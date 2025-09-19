#!/bin/bash
# Code198x Development Environment - Release Preparation Script

set -euo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSION=""
DRY_RUN=false
SKIP_TESTS=false

# Usage information
usage() {
    cat << EOF
Usage: $0 [OPTIONS] VERSION

Prepare a new release of the Code198x Development Environment.

Arguments:
    VERSION     Version to release (e.g., v1.0.0, v1.1.0-beta.1)

Options:
    -d, --dry-run       Show what would be done without making changes
    -s, --skip-tests    Skip build validation tests
    -h, --help          Show this help message

Examples:
    $0 v1.0.0           # Prepare stable release v1.0.0
    $0 v1.1.0-beta.1    # Prepare beta release
    $0 --dry-run v1.0.0 # Preview release process

EOF
}

# Logging functions
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -d|--dry-run)
            DRY_RUN=true
            shift
            ;;
        -s|--skip-tests)
            SKIP_TESTS=true
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        v*)
            VERSION="$1"
            shift
            ;;
        *)
            log_error "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
done

# Validate version argument
if [[ -z "$VERSION" ]]; then
    log_error "Version argument is required"
    usage
    exit 1
fi

# Validate version format
if ! [[ "$VERSION" =~ ^v[0-9]+\.[0-9]+\.[0-9]+(-[a-zA-Z0-9.-]+)?$ ]]; then
    log_error "Invalid version format. Use semantic versioning: vX.Y.Z or vX.Y.Z-prerelease"
    exit 1
fi

# Check if we're in the right directory
if [[ ! -f "$REPO_ROOT/VERSIONING.md" ]]; then
    log_error "Not in Code198x development environment repository root"
    exit 1
fi

# Pre-flight checks
log_info "Starting release preparation for $VERSION"

# Check git status
if [[ -n "$(git status --porcelain)" ]]; then
    log_error "Working directory is not clean. Please commit or stash changes."
    exit 1
fi

# Check if tag already exists
if git tag -l | grep -q "^$VERSION$"; then
    log_error "Tag $VERSION already exists"
    exit 1
fi

# Check if we're on main branch
CURRENT_BRANCH="$(git branch --show-current)"
if [[ "$CURRENT_BRANCH" != "main" ]]; then
    log_warning "You're not on the main branch (current: $CURRENT_BRANCH)"
    read -p "Continue anyway? [y/N] " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Pull latest changes
log_info "Pulling latest changes from remote"
if [[ "$DRY_RUN" == false ]]; then
    git pull origin main
fi

# Validate system count
log_info "Validating system configurations"
SYSTEM_COUNT=$(find "$REPO_ROOT/systems" -name "Dockerfile" | wc -l)
if [[ "$SYSTEM_COUNT" -ne 64 ]]; then
    log_error "Expected 64 systems, found $SYSTEM_COUNT"
    exit 1
fi
log_success "Found $SYSTEM_COUNT systems"

# Validate base images
BASE_COUNT=$(find "$REPO_ROOT/base-images" -name "Dockerfile" | wc -l)
if [[ "$BASE_COUNT" -ne 12 ]]; then
    log_error "Expected 12 base images, found $BASE_COUNT"
    exit 1
fi
log_success "Found $BASE_COUNT base images"

# Build validation (if not skipped)
if [[ "$SKIP_TESTS" == false ]]; then
    log_info "Running build validation tests..."

    # Test a sample of systems to validate Dockerfiles
    SAMPLE_SYSTEMS=("commodore-64" "nintendo-nes" "sega-genesis" "sony-playstation")

    for system in "${SAMPLE_SYSTEMS[@]}"; do
        log_info "Validating $system Dockerfile"
        if [[ "$DRY_RUN" == false ]]; then
            docker build --dry-run "$REPO_ROOT/systems/$system" > /dev/null
        fi
    done

    log_success "Build validation completed"
fi

# Generate changelog
log_info "Generating changelog"
PREVIOUS_TAG=$(git describe --tags --abbrev=0 2>/dev/null || echo "")

if [[ -n "$PREVIOUS_TAG" ]]; then
    log_info "Changes since $PREVIOUS_TAG:"
    git log --pretty=format:"  - %s" "$PREVIOUS_TAG..HEAD"
    echo
else
    log_info "This appears to be the first release"
fi

# Show release summary
echo
log_info "Release Summary"
echo "=================="
echo "Version: $VERSION"
echo "Previous tag: ${PREVIOUS_TAG:-"None (first release)"}"
echo "Systems: $SYSTEM_COUNT"
echo "Base images: $BASE_COUNT"
echo "Branch: $CURRENT_BRANCH"
echo "Dry run: $DRY_RUN"
echo

# Confirm release
if [[ "$DRY_RUN" == false ]]; then
    read -p "Create release $VERSION? [y/N] " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        log_info "Release cancelled"
        exit 0
    fi

    # Create and push tag
    log_info "Creating and pushing tag $VERSION"
    git tag "$VERSION"
    git push origin "$VERSION"

    log_success "Release tag created successfully!"
    log_info "GitHub Actions will now build and publish all containers"
    log_info "Monitor the workflow at: https://github.com/code198x/development-environment/actions"
else
    log_success "Dry run completed successfully!"
    log_info "Run without --dry-run to create the actual release"
fi

echo
log_info "Next steps:"
echo "1. Monitor GitHub Actions workflow completion"
echo "2. Verify all containers are published with $VERSION tag"
echo "3. Update documentation if needed"
echo "4. Announce release to educational community"