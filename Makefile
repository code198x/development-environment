# Code198x Development Environment Makefile
# Matrix-based build system for all retro platforms

.PHONY: all build push test clean matrix-build matrix-verify help

DOCKER_ORG := code198x
SYSTEMS := commodore-64 sinclair-zx-spectrum nintendo-entertainment-system commodore-amiga

# Default target
all: build

# Build all Docker images
build:
	@echo "🔨 Building all Docker images..."
	@./scripts/build-images.sh

# Build and push all images
push:
	@echo "🚀 Building and pushing all Docker images..."
	@./scripts/build-images.sh --push

# Build a specific system
build-%:
	@echo "🔨 Building $*..."
	@docker build -t $(DOCKER_ORG)/$*:latest $*/

# Test all systems
test:
	@echo "🧪 Testing all assemblers..."
	@for system in $(SYSTEMS); do \
		echo "Testing $$system..."; \
		docker run --rm -v $(PWD)/$$system:/workspace $(DOCKER_ORG)/$$system:latest test.asm || exit 1; \
	done

# Test a specific system
test-%:
	@echo "🧪 Testing $*..."
	@docker run --rm -v $(PWD)/$*:/workspace $(DOCKER_ORG)/$*:latest test.asm

# Generate GitHub Actions matrix
matrix-build:
	@node scripts/generate-matrix.mjs build

matrix-verify:
	@node scripts/generate-matrix.mjs verify

# Generate documentation table
docs-table:
	@node scripts/generate-matrix.mjs table

# Clean up Docker images
clean:
	@echo "🧹 Cleaning up Docker images..."
	@for system in $(SYSTEMS); do \
		docker rmi $(DOCKER_ORG)/$$system:latest 2>/dev/null || true; \
	done

# Show available systems
list-systems:
	@echo "Available systems:"
	@node -e "const config = require('./systems-config.json'); config.systems.forEach(s => console.log('  -', s.id, '(' + s.name + ')'))"

# Add a new system (scaffolding)
add-system:
	@echo "To add a new system:"
	@echo "1. Create directory: mkdir <system-id>"
	@echo "2. Add Dockerfile: <system-id>/Dockerfile"
	@echo "3. Add test file: <system-id>/test.asm"
	@echo "4. Update systems-config.json"
	@echo "5. Run: make build-<system-id>"

# Interactive development shell for any system
shell-%:
	@echo "🖥️  Starting $* development environment..."
	@docker run -it --rm \
		-v $(PWD)/workspace:/workspace \
		-v $(PWD)/projects/$*:/projects \
		-v $(PWD)/resources/$*:/resources:ro \
		-w /workspace \
		$(DOCKER_ORG)/$*:latest /bin/bash

# Quick access shells
c64: shell-commodore-64
nes: shell-nintendo-entertainment-system
spectrum: shell-sinclair-zx-spectrum
amiga: shell-commodore-amiga
genesis: shell-sega-genesis

# Create a new project for a system
new-project:
ifndef NAME
	$(error NAME is not set. Use: make new-project NAME=myproject SYSTEM=c64)
endif
ifndef SYSTEM
	$(error SYSTEM is not set. Use: make new-project NAME=myproject SYSTEM=c64)
endif
	@echo "📁 Creating new $(SYSTEM) project: $(NAME)"
	@mkdir -p projects/$(SYSTEM)/$(NAME)
	@echo "; $(NAME) - $(SYSTEM) Assembly Project" > projects/$(SYSTEM)/$(NAME)/main.asm
	@echo "; Created: $$(date)" >> projects/$(SYSTEM)/$(NAME)/main.asm
	@echo "" >> projects/$(SYSTEM)/$(NAME)/main.asm
	@echo "Project created at projects/$(SYSTEM)/$(NAME)"

# Development environment setup
dev-setup:
	@echo "🔧 Setting up development environment..."
	@mkdir -p workspace projects/{commodore-64,nintendo-entertainment-system,sinclair-zx-spectrum,commodore-amiga,sega-genesis}
	@echo "Development directories created"

# Run assembler in container
assemble:
ifndef FILE
	$(error FILE is not set. Use: make assemble FILE=main.asm SYSTEM=c64)
endif
ifndef SYSTEM
	$(error SYSTEM is not set. Use: make assemble FILE=main.asm SYSTEM=c64)
endif
	@echo "⚙️  Assembling $(FILE) for $(SYSTEM)..."
	@docker run --rm \
		-v $(PWD)/projects/$(SYSTEM):/workspace \
		$(DOCKER_ORG)/$(SYSTEM):latest $(FILE)

# Help
help:
	@echo "Code198x Development Environment - Make targets"
	@echo ""
	@echo "Quick Start:"
	@echo "  make dev-setup      - Set up development directories"
	@echo "  make c64            - Start Commodore 64 shell"
	@echo "  make nes            - Start NES shell"
	@echo "  make spectrum       - Start ZX Spectrum shell"
	@echo "  make amiga          - Start Amiga shell"
	@echo "  make genesis        - Start Sega Genesis shell"
	@echo ""
	@echo "Development:"
	@echo "  make shell-<system> - Start development shell for system"
	@echo "  make new-project NAME=<name> SYSTEM=<system> - Create new project"
	@echo "  make assemble FILE=<file> SYSTEM=<system>    - Assemble file"
	@echo ""
	@echo "Building:"
	@echo "  make build          - Build all Docker images"
	@echo "  make build-<system> - Build specific system image"
	@echo "  make push           - Build and push all images"
	@echo ""
	@echo "Testing:"
	@echo "  make test           - Test all systems"
	@echo "  make test-<system>  - Test specific system"
	@echo ""
	@echo "Matrix Generation:"
	@echo "  make matrix-build   - Generate build matrix"
	@echo "  make matrix-verify  - Generate verify matrix"
	@echo "  make docs-table     - Generate documentation table"
	@echo ""
	@echo "Utilities:"
	@echo "  make list-systems   - Show available systems"
	@echo "  make add-system     - Instructions for adding new system"
	@echo "  make clean          - Remove Docker images"
	@echo "  make help           - Show this help"
	@echo ""
	@echo "Available systems:"
	@for system in $(SYSTEMS); do echo "  - $$system"; done