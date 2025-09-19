# GitLab Mirror Setup Guide

This guide walks through setting up GitLab as a mirror for the Code198x Development Environment, providing platform redundancy and additional container registry options.

## 1. GitLab Group and Repository Setup

### Create GitLab Group (Organization)

1. Go to [GitLab.com](https://gitlab.com) and sign in
2. Click the **"+"** icon in the top navbar
3. Select **"New group"**
4. Choose **"Create group"** (not "Import group")
5. Configure group:
   - **Group name**: `Code198x`
   - **Group URL**: `code198x` (creates `gitlab.com/code198x`)
   - **Visibility level**: Public (for educational use)
   - **Description**: "Retro gaming development environments for education"
6. Click **"Create group"**

### Create Project Within Group

1. From your Code198x group page, click **"New project"**
2. Choose **"Import project"** → **"Repository by URL"**
3. Configure import:
   - **Git repository URL**: `https://github.com/code198x/development-environment.git`
   - **Project name**: `development-environment`
   - **Project slug**: `development-environment`
   - **Visibility level**: Public (for educational use)
4. Final URL will be: `gitlab.com/code198x/development-environment`

### Enable Container Registry

1. In your GitLab project, go to **Settings** → **General**
2. Expand **Visibility, project features, permissions**
3. Ensure **Container Registry** is enabled
4. Note your registry URL: `registry.gitlab.com/code198x/development-environment`

## 2. Repository Mirroring

### Option A: GitLab Pull Mirroring (Recommended)

1. In GitLab project, go to **Settings** → **Repository**
2. Expand **Mirroring repositories**
3. Add mirror:
   - **Git repository URL**: `https://github.com/code198x/development-environment.git`
   - **Mirror direction**: Pull
   - **Authentication method**: None (for public repo)
   - **Keep divergent refs**: Checked
4. Click **Mirror repository**

### Option B: GitHub Push Mirroring

Add GitLab as a push target in GitHub repository settings.

## 3. CI/CD Variables

Configure the following variables in **Settings** → **CI/CD** → **Variables**:

### Required Variables

```bash
# Docker Hub (optional - for triple redundancy)
DOCKER_HUB_USERNAME     # Your Docker Hub username
DOCKER_HUB_TOKEN        # Docker Hub access token

# GitLab Container Registry (automatically available)
CI_REGISTRY_USER        # Automatically provided
CI_REGISTRY_PASSWORD    # Automatically provided
```

### Variable Settings
- **Protected**: Yes (for tagged releases)
- **Masked**: Yes (for tokens)
- **Environment scope**: All

## 4. Container Registry Configuration

### GitLab Container Registry URLs

Your containers will be available at:

```bash
# Base images
registry.gitlab.com/code198x/development-environment/code198x-base:v1.0.0
registry.gitlab.com/code198x/development-environment/6502-base:v1.0.0
# ... all 12 base images

# Gaming systems
registry.gitlab.com/code198x/development-environment/commodore-64:v1.0.0
registry.gitlab.com/code198x/development-environment/nintendo-nes:v1.0.0
# ... all 64 gaming systems
```

### Registry Authentication

```bash
# For users pulling containers
docker login registry.gitlab.com
# Use GitLab username and access token

# Pull containers
docker pull registry.gitlab.com/code198x/development-environment/commodore-64:v1.0.0
```

## 5. Release Process

### Automated Releases

When you create a GitHub release (via tag):

1. **GitHub Actions** builds and pushes to:
   - GitHub Container Registry (`ghcr.io/code198x/`)
   - Docker Hub (`code198x/`) - if configured

2. **GitLab CI/CD** automatically triggers and pushes to:
   - GitLab Container Registry (`registry.gitlab.com/[username]/development-environment/`)

### Manual Releases

You can trigger builds manually in GitLab:

1. Go to **CI/CD** → **Pipelines**
2. Click **Run pipeline**
3. Select branch or tag
4. Run pipeline

## 6. Educational Documentation

### For Educators Using GitLab

Update your course materials to reference both platforms:

```bash
# Primary (GitHub)
docker pull ghcr.io/code198x/commodore-64:v1.0.0

# Alternative (GitLab)
docker pull registry.gitlab.com/code198x/development-environment/commodore-64:v1.0.0

# Backup (Docker Hub) - if available
docker pull code198x/commodore-64:v1.0.0
```

### Institution-Specific Setup

Some educational institutions prefer GitLab:

1. Provide GitLab registry URLs in course materials
2. Include GitLab authentication instructions
3. Mention GitHub as primary source for documentation

## 7. Monitoring and Maintenance

### Pipeline Status

Monitor both platforms:
- **GitHub**: Actions tab for build status
- **GitLab**: CI/CD → Pipelines for mirror status

### Storage Quotas

GitLab.com free tier includes:
- 10GB storage for container registry
- 400 CI/CD minutes per month

Monitor usage in **Settings** → **Usage Quotas**.

### Sync Verification

Periodically verify mirrors are in sync:

```bash
# Compare latest tags
git ls-remote --tags https://github.com/code198x/development-environment.git
git ls-remote --tags https://gitlab.com/code198x/development-environment.git
```

## 8. Troubleshooting

### Mirror Not Updating

1. Check **Settings** → **Repository** → **Mirroring repositories**
2. Look for error messages
3. Verify GitHub repository is public
4. Try manual update

### CI/CD Pipeline Failures

1. Check **CI/CD** → **Pipelines** for specific job failures
2. Review job logs for Docker build errors
3. Verify CI/CD variables are set correctly
4. Check GitLab Container Registry permissions

### Registry Authentication Issues

1. Verify access token has registry permissions
2. Check if 2FA is enabled (requires personal access token)
3. Ensure registry is enabled in project settings

## 9. Benefits Achieved

✅ **Platform redundancy** - Survive GitHub outages or policy changes
✅ **Educational choice** - Institutions can use preferred platform
✅ **Global distribution** - GitLab's different CDN for international access
✅ **Cost resilience** - Multiple free tiers reduce hosting risk
✅ **Digital preservation** - Multiple copies prevent loss

## 10. Next Steps

Once GitLab mirroring is active:

1. Test container pulls from GitLab registry
2. Update documentation to mention both platforms
3. Notify educational community about additional access option
4. Monitor usage across both platforms
5. Consider automating health checks across registries

---

**Note**: This guide assumes you've created the `code198x` GitLab Group as described. All container registry URLs will use the `code198x` namespace for consistency with the GitHub organization.