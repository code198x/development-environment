# GitHub Container Registry (GHCR) Setup for Organizations

## Issue: "installation not allowed to Create organization package"

This error occurs when GitHub Actions doesn't have permission to create packages in an organization. Here's how to fix it:

## Solution 1: Enable GitHub Actions Package Creation (Recommended)

### For Organization Owners:

1. Go to your organization settings: https://github.com/organizations/code198x/settings/packages
2. Under "Package Creation", ensure these are enabled:
   - ✅ Members can publish public packages
   - ✅ GitHub Actions can create and approve pull requests

3. For the repository:
   - Go to: https://github.com/code198x/development-environment/settings/actions
   - Under "Workflow permissions", select:
     - ✅ Read and write permissions
     - ✅ Allow GitHub Actions to create and approve pull requests

## Solution 2: Use Personal Account Namespace (Alternative)

If you can't modify organization settings, you can push to your personal namespace instead:

1. Edit `.github/workflows/docker-build.yml`
2. Change `GHCR_ORG: ghcr.io/code198x` to `GHCR_ORG: ghcr.io/${{ github.repository_owner }}`

This will push images to `ghcr.io/<your-username>/<system>` instead.

## Solution 3: Create Packages Manually First

Sometimes GitHub requires packages to exist before Actions can push to them:

1. Build and push an image manually from your local machine:
```bash
# Login to GHCR
echo $GITHUB_TOKEN | docker login ghcr.io -u YOUR_USERNAME --password-stdin

# Build an image
docker build -t ghcr.io/code198x/commodore-64:latest systems/commodore-64/

# Push it (this creates the package)
docker push ghcr.io/code198x/commodore-64:latest
```

2. After the package exists, GitHub Actions should be able to push to it

## Verifying Permissions

Check current permissions:
1. Go to: https://github.com/code198x/development-environment/settings/actions
2. Verify "Workflow permissions" shows read/write
3. Check that the workflow file includes:
```yaml
permissions:
  contents: read
  packages: write
```

## Package Visibility

After packages are created, you may want to:
1. Go to: https://github.com/orgs/code198x/packages
2. Click on each package
3. Under "Package settings", set visibility to "Public"
4. Link the package to the repository for better discoverability

## Troubleshooting

If issues persist:
- Ensure the organization has GitHub Packages enabled
- Check if there are any IP restrictions or security policies
- Try using a Personal Access Token with `write:packages` scope
- Contact GitHub Support if organizational policies are blocking package creation

## Using the Images

Once working, images will be available at:
- `ghcr.io/code198x/commodore-64:latest`
- `ghcr.io/code198x/sinclair-zx-spectrum:latest`
- `ghcr.io/code198x/nintendo-entertainment-system:latest`
- `ghcr.io/code198x/commodore-amiga:latest`

No authentication needed to pull public images:
```bash
docker pull ghcr.io/code198x/commodore-64:latest
```