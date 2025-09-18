# Development Environment Setup Guide

## Setting up Docker Hub Credentials for CI/CD

To enable automatic Docker image builds and publishing, you need to configure Docker Hub credentials as GitHub repository secrets.

### Prerequisites

1. Docker Hub account (free at https://hub.docker.com)
2. Repository admin access on GitHub

### Steps

#### 1. Create Docker Hub Access Token

1. Log in to Docker Hub: https://hub.docker.com
2. Go to Account Settings → Security
3. Click "New Access Token"
4. Name: `github-actions-code198x`
5. Permissions: `Read & Write`
6. Click "Generate"
7. **Copy the token immediately** (you won't see it again)

#### 2. Add Secrets to GitHub Repository

1. Go to your repository: https://github.com/code198x/development-environment
2. Navigate to Settings → Secrets and variables → Actions
3. Click "New repository secret"

Add these two secrets:

**Secret 1: DOCKER_USERNAME**
- Name: `DOCKER_USERNAME`
- Value: Your Docker Hub username

**Secret 2: DOCKER_TOKEN**
- Name: `DOCKER_TOKEN`
- Value: The access token you copied from Docker Hub

#### 3. Verify Setup

After adding the secrets:
1. Push a change to the repository
2. Check Actions tab for build status
3. Images should be published to: https://hub.docker.com/u/code198x

## Local Development Without Docker Hub

If you don't have Docker Hub credentials configured, the workflow will:
- ✅ Build images locally for testing
- ✅ Run all verification tests
- ⚠️ Skip pushing to Docker Hub
- ℹ️ Display a warning message

This allows contributors to test changes without needing Docker Hub access.

## Manual Build and Push

To manually build and push images (requires Docker Hub login):

```bash
# Login to Docker Hub
docker login

# Build all images
make build

# Push all images
make push

# Or build/push specific system
make build-commodore-64
docker push code198x/commodore-64:latest
```

## Troubleshooting

### "Username and password required" error
- Secrets are not configured in GitHub repository
- Follow steps above to add DOCKER_USERNAME and DOCKER_TOKEN

### "denied: requested access to the resource is denied"
- Docker Hub organization doesn't exist or you don't have access
- Create organization at: https://hub.docker.com/orgs

### Images build but don't push
- Check if credentials are configured correctly
- Verify Docker Hub access token has write permissions
- Check organization membership and permissions