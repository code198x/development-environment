#!/bin/bash

# Code198x Development Environment Installer
# Supports macOS and Linux

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# ASCII Art Banner
echo -e "${BLUE}"
cat << 'EOF'
   ╔═══════════════════════════════════════╗
   ║          Code198x Dev Environment     ║
   ║        Vintage Computing Setup        ║
   ╚═══════════════════════════════════════╝
EOF
echo -e "${NC}"

# Detect OS
OS="unknown"
case "$(uname -s)" in
    Darwin*)    OS="macos";;
    Linux*)     OS="linux";;
    CYGWIN*|MINGW*|MSYS*) OS="windows";;
esac

echo -e "${BLUE}🖥️  Detected OS: ${OS}${NC}"

# Check prerequisites
check_prerequisites() {
    echo -e "\n${YELLOW}📋 Checking prerequisites...${NC}"
    
    # Check if running as root (not recommended)
    if [[ $EUID -eq 0 ]]; then
        echo -e "${RED}❌ Please don't run this installer as root${NC}"
        exit 1
    fi
    
    # Check disk space (need at least 2GB)
    AVAILABLE=$(df . | tail -1 | awk '{print $4}')
    if [[ $AVAILABLE -lt 2097152 ]]; then  # 2GB in KB
        echo -e "${RED}❌ Need at least 2GB free disk space${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}✅ Prerequisites check passed${NC}"
}

# Install package manager if needed
install_package_manager() {
    case $OS in
        "macos")
            if ! command -v brew &> /dev/null; then
                echo -e "\n${YELLOW}🍺 Installing Homebrew...${NC}"
                /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
                
                # Add brew to PATH for Apple Silicon Macs
                if [[ -f "/opt/homebrew/bin/brew" ]]; then
                    echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
                    eval "$(/opt/homebrew/bin/brew shellenv)"
                fi
            else
                echo -e "${GREEN}✅ Homebrew already installed${NC}"
            fi
            ;;
        "linux")
            # Update package lists
            echo -e "\n${YELLOW}📦 Updating package lists...${NC}"
            if command -v apt-get &> /dev/null; then
                sudo apt-get update
            elif command -v dnf &> /dev/null; then
                sudo dnf check-update || true
            elif command -v pacman &> /dev/null; then
                sudo pacman -Sy
            fi
            ;;
    esac
}

# Install system tools
install_system_tools() {
    echo -e "\n${YELLOW}🔧 Installing system tools...${NC}"
    
    case $OS in
        "macos")
            # Essential tools
            brew install git wget curl unzip
            echo -e "${GREEN}✅ System tools installed${NC}"
            ;;
        "linux")
            if command -v apt-get &> /dev/null; then
                sudo apt-get install -y git wget curl unzip build-essential
            elif command -v dnf &> /dev/null; then
                sudo dnf install -y git wget curl unzip gcc gcc-c++ make
            elif command -v pacman &> /dev/null; then
                sudo pacman -S --noconfirm git wget curl unzip base-devel
            fi
            echo -e "${GREEN}✅ System tools installed${NC}"
            ;;
    esac
}

# Install Commodore 64 tools
install_c64_tools() {
    echo -e "\n${YELLOW}🖥️  Installing Commodore 64 tools...${NC}"
    
    case $OS in
        "macos")
            # ACME assembler
            if ! command -v acme &> /dev/null; then
                brew install acme
            fi
            
            # VICE emulator
            if ! command -v x64sc &> /dev/null; then
                brew install --cask vice
            fi
            ;;
        "linux")
            # ACME assembler
            if ! command -v acme &> /dev/null; then
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y acme
                else
                    # Build from source if not available
                    echo -e "${YELLOW}📦 Building ACME from source...${NC}"
                    mkdir -p tools/src
                    cd tools/src
                    wget -O acme.tar.gz https://sourceforge.net/projects/acme-crossass/files/latest/download
                    tar xzf acme.tar.gz
                    cd ACME*/src
                    make
                    sudo cp acme /usr/local/bin/
                    cd ../../../..
                fi
            fi
            
            # VICE emulator
            if ! command -v x64sc &> /dev/null; then
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y vice
                elif command -v dnf &> /dev/null; then
                    sudo dnf install -y vice
                elif command -v pacman &> /dev/null; then
                    sudo pacman -S --noconfirm vice
                fi
            fi
            ;;
    esac
    
    echo -e "${GREEN}✅ Commodore 64 tools installed${NC}"
}

# Install ZX Spectrum tools
install_spectrum_tools() {
    echo -e "\n${YELLOW}🌈 Installing ZX Spectrum tools...${NC}"
    
    case $OS in
        "macos")
            # PASMO assembler
            if ! command -v pasmo &> /dev/null; then
                brew install pasmo
            fi
            
            # Fuse emulator
            if ! command -v fuse &> /dev/null; then
                brew install --cask fuse-emulator
            fi
            ;;
        "linux")
            # PASMO assembler
            if ! command -v pasmo &> /dev/null; then
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y pasmo
                else
                    # Build from source
                    echo -e "${YELLOW}📦 Building PASMO from source...${NC}"
                    mkdir -p tools/src
                    cd tools/src
                    wget http://pasmo.speccy.org/pasmo-0.5.4.beta2.tgz
                    tar xzf pasmo-0.5.4.beta2.tgz
                    cd pasmo-*
                    ./configure
                    make
                    sudo make install
                    cd ../../..
                fi
            fi
            
            # Fuse emulator
            if ! command -v fuse &> /dev/null; then
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y fuse-emulator
                elif command -v dnf &> /dev/null; then
                    sudo dnf install -y fuse-emulator
                elif command -v pacman &> /dev/null; then
                    sudo pacman -S --noconfirm fuse-emulator
                fi
            fi
            ;;
    esac
    
    echo -e "${GREEN}✅ ZX Spectrum tools installed${NC}"
}

# Install Amiga tools
install_amiga_tools() {
    echo -e "\n${YELLOW}🎨 Installing Amiga tools...${NC}"
    
    # VASM assembler (build from source - not in package managers)
    if ! command -v vasmm68k_mot &> /dev/null; then
        echo -e "${YELLOW}📦 Building VASM from source...${NC}"
        mkdir -p tools/src
        cd tools/src
        
        if [ ! -d "vasm" ]; then
            wget http://sun.hasenbraten.de/vasm/release/vasm.tar.gz
            tar xzf vasm.tar.gz
            mv vasm* vasm
        fi
        
        cd vasm
        make CPU=m68k SYNTAX=mot
        
        # Install to tools directory
        mkdir -p ../../bin
        cp vasmm68k_mot vobjdump ../../bin/
        
        # Add to PATH for this session
        export PATH="$(pwd)/../../bin:$PATH"
        
        cd ../../..
    fi
    
    # FS-UAE emulator
    case $OS in
        "macos")
            if ! command -v fs-uae &> /dev/null; then
                echo -e "${YELLOW}📦 Installing FS-UAE...${NC}"
                # Download and install FS-UAE
                wget -O /tmp/fs-uae.zip https://fs-uae.net/stable/macos-x86-64/fs-uae_3.1.66_macos-x86-64.zip
                cd /tmp
                unzip -q fs-uae.zip
                mv FS-UAE.app /Applications/
                ln -sf /Applications/FS-UAE.app/Contents/MacOS/fs-uae /usr/local/bin/fs-uae 2>/dev/null || true
                cd - > /dev/null
            fi
            ;;
        "linux")
            if ! command -v fs-uae &> /dev/null; then
                echo -e "${YELLOW}📦 Installing FS-UAE...${NC}"
                # Try package manager first
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y fs-uae || {
                        # Download AppImage if package not available
                        wget -O tools/bin/fs-uae https://fs-uae.net/stable/linux-x86-64/fs-uae_3.1.66_linux-x86-64.AppImage
                        chmod +x tools/bin/fs-uae
                    }
                fi
            fi
            ;;
    esac
    
    echo -e "${GREEN}✅ Amiga tools installed${NC}"
}

# Install NES tools
install_nes_tools() {
    echo -e "\n${YELLOW}🎮 Installing NES tools...${NC}"
    
    case $OS in
        "macos")
            # CC65 toolkit
            if ! command -v ca65 &> /dev/null; then
                brew install cc65
            fi
            
            # Mesen emulator
            if ! command -v mesen &> /dev/null; then
                brew install --cask mesen
            fi
            ;;
        "linux")
            # CC65 toolkit
            if ! command -v ca65 &> /dev/null; then
                if command -v apt-get &> /dev/null; then
                    sudo apt-get install -y cc65
                elif command -v dnf &> /dev/null; then
                    sudo dnf install -y cc65
                elif command -v pacman &> /dev/null; then
                    sudo pacman -S --noconfirm cc65
                fi
            fi
            
            # Mesen emulator
            if ! command -v mesen &> /dev/null; then
                echo -e "${YELLOW}📦 Installing Mesen...${NC}"
                mkdir -p tools/bin
                wget -O tools/bin/mesen https://github.com/SourMesen/Mesen2/releases/latest/download/linux-x64.tar.gz
                cd tools/bin
                tar xzf mesen
                chmod +x Mesen
                ln -sf $(pwd)/Mesen mesen
                cd ../..
            fi
            ;;
    esac
    
    echo -e "${GREEN}✅ NES tools installed${NC}"
}

# Create project templates
create_templates() {
    echo -e "\n${YELLOW}📁 Creating project templates...${NC}"
    
    # Copy templates from our repo structure
    mkdir -p templates
    
    # Each template will be created by separate functions
    create_c64_template
    create_spectrum_template  
    create_amiga_template
    create_nes_template
    
    echo -e "${GREEN}✅ Project templates created${NC}"
}

# Create Commodore 64 template
create_c64_template() {
    mkdir -p templates/c64-basic
    
    cat > templates/c64-basic/main.s << 'EOF'
; Code198x Commodore 64 Template
; Basic "Hello World" program

*= $0801

; BASIC stub: 10 SYS 2061
!word next_line
!word 10
!byte $9e
!text "2061"
!byte 0
next_line:
!word 0

; Main program starts here
start:
    ; Set border and background colors
    lda #$06        ; Blue
    sta $d020       ; Border
    lda #$00        ; Black  
    sta $d021       ; Background
    
    ; Print "HELLO WORLD" message
    ldy #0
print_loop:
    lda message,y
    beq done
    jsr $ffd2       ; CHROUT
    iny
    bne print_loop
    
done:
    rts

message: !text "HELLO, CODE198X WORLD!", 13, 0
EOF

    cat > templates/c64-basic/build.sh << 'EOF'
#!/bin/bash
echo "Building Commodore 64 program..."
acme -f cbm -o hello.prg main.s
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    if command -v x64sc &> /dev/null; then
        echo "🚀 Launching VICE..."
        x64sc hello.prg
    else
        echo "⚠️  VICE not found. Install with: brew install --cask vice"
    fi
else
    echo "❌ Build failed!"
fi
EOF

    chmod +x templates/c64-basic/build.sh
    
    cat > templates/c64-basic/README.md << 'EOF'
# Commodore 64 Basic Template

Simple "Hello World" program for the Commodore 64.

## Building

```bash
./build.sh
```

## What it does

- Sets border to blue and background to black
- Prints "HELLO, CODE198X WORLD!" to the screen
- Uses BASIC stub for easy loading

## Next steps

- Modify the message
- Change colors
- Add graphics or sound
- Check out the Code198x lessons for more advanced techniques!
EOF
}

# Create ZX Spectrum template
create_spectrum_template() {
    mkdir -p templates/spectrum-basic
    
    cat > templates/spectrum-basic/main.z80 << 'EOF'
; Code198x ZX Spectrum Template
; Color demo program

        ORG $8000

start:
        ; Clear screen
        CALL clear_screen
        
        ; Set border to cyan
        LD A, 5
        OUT (254), A
        
        ; Draw colored message
        CALL draw_message
        
        ; Wait for key
        CALL wait_key
        
        ; Return to BASIC
        RET

clear_screen:
        ; Clear display memory
        LD HL, $4000
        LD DE, $4001
        LD BC, $17FF
        LD (HL), 0
        LDIR
        
        ; Set attributes to white on black
        LD HL, $5800
        LD DE, $5801
        LD BC, $2FF
        LD (HL), $07
        LDIR
        
        RET

draw_message:
        ; Position at row 10, column 8
        LD HL, $4000 + 10*32 + 8
        LD DE, message
        LD B, message_end - message
        
draw_loop:
        LD A, (DE)
        LD (HL), A
        INC HL
        INC DE
        DJNZ draw_loop
        
        ; Set colors - rainbow effect
        LD HL, $5800 + 10*32 + 8
        LD B, message_end - message
        LD A, $42       ; Start with red
        
color_loop:
        LD (HL), A
        INC HL
        INC A
        AND $47         ; Keep in color range
        OR $40          ; Keep bright bit
        DJNZ color_loop
        
        RET

wait_key:
        LD A, $7F
        IN A, (254)
        AND $1F
        CP $1F
        JR Z, wait_key
        RET

message:    DB "HELLO, CODE198X!"
message_end:

        END start
EOF

    cat > templates/spectrum-basic/build.sh << 'EOF'
#!/bin/bash
echo "Building ZX Spectrum program..."
pasmo --tap main.z80 hello.tap
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    if command -v fuse &> /dev/null; then
        echo "🚀 Launching Fuse..."
        fuse hello.tap
    else
        echo "⚠️  Fuse not found. Install with: brew install --cask fuse-emulator"
    fi
else
    echo "❌ Build failed!"
fi
EOF

    chmod +x templates/spectrum-basic/build.sh
    
    cat > templates/spectrum-basic/README.md << 'EOF'
# ZX Spectrum Basic Template

Colorful "Hello World" program for the ZX Spectrum.

## Building

```bash
./build.sh
```

## What it does

- Clears the screen to black
- Sets cyan border color
- Displays "HELLO, CODE198X!" with rainbow colors
- Waits for any key press

## Next steps

- Experiment with different colors
- Add graphics and patterns
- Try the ZX Spectrum lessons for advanced techniques!
EOF
}

# Create Amiga template
create_amiga_template() {
    mkdir -p templates/amiga-basic
    
    cat > templates/amiga-basic/main.s << 'EOF'
; Code198x Amiga Template
; Simple bitplane graphics demo

        section code,code

start:
        ; Open graphics library
        move.l  execbase,a6
        lea     gfxname,a1
        moveq   #0,d0
        jsr     -552(a6)        ; OpenLibrary
        move.l  d0,gfxbase
        beq     exit
        
        ; Get screen info
        move.l  d0,a6
        jsr     -222(a6)        ; LockLayerRom
        
        ; Simple bitplane pattern
        move.l  #bitplane_data,a0
        move.w  #255,d0         ; 256 bytes
        
fill_loop:
        move.b  d0,(a0)+        ; Create pattern
        dbf     d0,fill_loop
        
        ; Wait a bit
        move.l  #1000000,d0
delay:
        subq.l  #1,d0
        bne     delay
        
        ; Close library
        move.l  execbase,a6
        move.l  gfxbase,a1
        jsr     -414(a6)        ; CloseLibrary

exit:
        moveq   #0,d0
        rts

gfxname:        dc.b    'graphics.library',0
                even

gfxbase:        dc.l    0
execbase        equ     4

bitplane_data:
        ds.b    256             ; Bitplane buffer

        end
EOF

    cat > templates/amiga-basic/build.sh << 'EOF'
#!/bin/bash
echo "Building Amiga program..."

# Check if vasm is available
if ! command -v vasmm68k_mot &> /dev/null; then
    echo "❌ VASM not found. Please run the installer first."
    exit 1
fi

vasmm68k_mot -Fhunkexe -o hello main.s
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    if command -v fs-uae &> /dev/null; then
        echo "🚀 Launching FS-UAE..."
        echo "📝 Copy 'hello' to your Amiga disk image and run it"
        fs-uae
    else
        echo "⚠️  FS-UAE not found. Manual installation required."
    fi
else
    echo "❌ Build failed!"
fi
EOF

    chmod +x templates/amiga-basic/build.sh
    
    cat > templates/amiga-basic/README.md << 'EOF'
# Amiga Basic Template

Simple graphics demo for the Commodore Amiga.

## Building

```bash
./build.sh
```

## What it does

- Opens the graphics library
- Creates a simple bitplane pattern
- Demonstrates basic Amiga system calls

## Next steps

- Add more sophisticated graphics
- Experiment with copper effects
- Try the Amiga lessons for advanced techniques!
EOF
}

# Create NES template  
create_nes_template() {
    mkdir -p templates/nes-basic
    
    # Copy the NES include file
    cp tools/nes.inc templates/nes-basic/ 2>/dev/null || {
        cat > templates/nes-basic/nes.inc << 'EOF'
; Basic NES definitions
PPUCTRL     = $2000
PPUMASK     = $2001  
PPUSTATUS   = $2002
PPUADDR     = $2006
PPUDATA     = $2007
EOF
    }
    
    cat > templates/nes-basic/main.s << 'EOF'
; Code198x NES Template
; Simple sprite demo

.segment "HEADER"
        .byte "NES", $1A
        .byte 2, 1, $01, $00
        .byte $00, $00, $00, $00, $00, $00, $00, $00

.include "nes.inc"

.segment "ZEROPAGE"
frame_count: .res 1

.segment "CODE"

RESET:
        sei
        cld
        ldx #$ff
        txs
        
        ; Wait for PPU
        bit $2002
:       bit $2002
        bpl :-
        
        ; Clear RAM
        lda #0
        ldx #0
:       sta $0000,x
        sta $0100,x
        sta $0200,x
        sta $0300,x
        inx
        bne :-
        
        ; Second wait
:       bit $2002
        bpl :-
        
        ; Setup
        jsr load_palette
        jsr setup_sprite
        
        ; Enable rendering
        lda #%10000000
        sta $2000
        lda #%00010000
        sta $2001

game_loop:
        inc frame_count
        jmp game_loop

load_palette:
        lda $2002
        lda #$3f
        sta $2006
        lda #$10
        sta $2006
        
        lda #$0f
        sta $2007
        lda #$30
        sta $2007
        lda #$27
        sta $2007
        lda #$15
        sta $2007
        
        rts

setup_sprite:
        lda #120        ; Y
        sta $0200
        lda #$01        ; Tile
        sta $0201
        lda #$00        ; Attributes
        sta $0202
        lda #128        ; X
        sta $0203
        
        rts

NMI:
        lda #$00
        sta $2003
        lda #$02
        sta $4014
        rti

IRQ:
        rti

.segment "VECTORS"
        .word NMI, RESET, IRQ

.segment "CHARS"
        .incbin "graphics.chr"
EOF

    # Create minimal CHR file
    dd if=/dev/zero of=templates/nes-basic/graphics.chr bs=8192 count=1 2>/dev/null || {
        # Fallback if dd not available
        head -c 8192 /dev/zero > templates/nes-basic/graphics.chr 2>/dev/null || {
            # Create empty file as last resort
            touch templates/nes-basic/graphics.chr
        }
    }
    
    cat > templates/nes-basic/nes.cfg << 'EOF'
MEMORY {
    ZP:     start = $0000, size = $0100, type = rw, file = "";
    HEADER: start = $0000, size = $0010, type = ro, file = %O, fill = yes;
    PRG:    start = $8000, size = $8000, type = ro, file = %O, fill = yes;
    CHR:    start = $0000, size = $2000, type = ro, file = %O, fill = yes;
}

SEGMENTS {
    ZEROPAGE: load = ZP, type = zp;
    HEADER:   load = HEADER, type = ro;
    CODE:     load = PRG, type = ro, start = $8000;
    VECTORS:  load = PRG, type = ro, start = $FFFA;
    CHARS:    load = CHR, type = ro;
}
EOF

    cat > templates/nes-basic/build.sh << 'EOF'
#!/bin/bash
echo "Building NES program..."
ca65 main.s -o main.o
if [ $? -eq 0 ]; then
    ld65 main.o -C nes.cfg -o hello.nes
    if [ $? -eq 0 ]; then
        echo "✅ Build successful!"
        if command -v mesen &> /dev/null; then
            echo "🚀 Launching Mesen..."
            mesen hello.nes
        else
            echo "⚠️  Mesen not found. Install manually or use another NES emulator."
        fi
    else
        echo "❌ Linking failed!"
    fi
else
    echo "❌ Assembly failed!"
fi
EOF

    chmod +x templates/nes-basic/build.sh
    
    cat > templates/nes-basic/README.md << 'EOF'
# NES Basic Template

Simple sprite demo for the Nintendo Entertainment System.

## Building

```bash
./build.sh
```

## What it does

- Initializes the NES hardware
- Sets up a basic color palette
- Displays a sprite in the center of the screen
- Demonstrates proper NES program structure

## Next steps

- Add controller input
- Create animated sprites
- Add background graphics
- Try the NES lessons for advanced techniques!
EOF
}

# Create build scripts
create_build_scripts() {
    echo -e "\n${YELLOW}🔨 Creating build scripts...${NC}"
    
    mkdir -p scripts
    
    # Main project creation script
    cat > scripts/new-project.sh << 'EOF'
#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <system> <project-name>"
    echo "Systems: c64, spectrum, amiga, nes"
    exit 1
fi

SYSTEM=$1
PROJECT=$2

if [ ! -d "templates/${SYSTEM}-basic" ]; then
    echo "❌ Unknown system: $SYSTEM"
    echo "Available: c64, spectrum, amiga, nes"
    exit 1
fi

if [ -d "$PROJECT" ]; then
    echo "❌ Project directory '$PROJECT' already exists"
    exit 1
fi

echo "📁 Creating $SYSTEM project: $PROJECT"
cp -r "templates/${SYSTEM}-basic" "$PROJECT"

echo "✅ Project created successfully!"
echo "🚀 To build and run:"
echo "   cd $PROJECT"
echo "   ./build.sh"
EOF

    chmod +x scripts/new-project.sh
    
    echo -e "${GREEN}✅ Build scripts created${NC}"
}

# Create VS Code integration
create_vscode_integration() {
    echo -e "\n${YELLOW}💻 Creating VS Code integration...${NC}"
    
    mkdir -p vscode
    
    # VS Code settings
    cat > vscode/settings.json << 'EOF'
{
    "files.associations": {
        "*.s": "asm6502",
        "*.asm": "asm6502", 
        "*.z80": "z80-asm",
        "*.inc": "asm6502"
    },
    "editor.insertSpaces": true,
    "editor.tabSize": 8,
    "editor.detectIndentation": false,
    "files.eol": "\n",
    "terminal.integrated.shell.osx": "/bin/bash",
    "terminal.integrated.shell.linux": "/bin/bash"
}
EOF

    # Recommended extensions
    cat > vscode/extensions.json << 'EOF'
{
    "recommendations": [
        "13xforever.language-x86-64-assembly",
        "maziac.asm-code-lens",
        "ms-vscode.hexeditor",
        "alefragnani.project-manager"
    ]
}
EOF

    # Build tasks
    cat > vscode/tasks.json << 'EOF'
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build C64",
            "type": "shell",
            "command": "./build.sh",
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": []
        },
        {
            "label": "Build Spectrum",
            "type": "shell", 
            "command": "./build.sh",
            "group": "build",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            },
            "problemMatcher": []
        }
    ]
}
EOF

    echo -e "${GREEN}✅ VS Code integration created${NC}"
}

# Test installation
test_installation() {
    echo -e "\n${YELLOW}🧪 Testing installation...${NC}"
    
    FAILED_TESTS=0
    
    # Test each system
    for SYSTEM in c64 spectrum amiga nes; do
        echo -e "\n${BLUE}Testing ${SYSTEM}...${NC}"
        
        if [ -d "templates/${SYSTEM}-basic" ]; then
            echo -e "  ✅ Template exists"
            
            # Test build script exists and is executable
            if [ -x "templates/${SYSTEM}-basic/build.sh" ]; then
                echo -e "  ✅ Build script is executable"
            else
                echo -e "  ❌ Build script missing or not executable"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
        else
            echo -e "  ❌ Template missing"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    done
    
    # Test project creation script
    if [ -x "scripts/new-project.sh" ]; then
        echo -e "  ✅ Project creation script ready"
    else
        echo -e "  ❌ Project creation script missing"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "\n${GREEN}🎉 All tests passed!${NC}"
        return 0
    else
        echo -e "\n${RED}❌ $FAILED_TESTS tests failed${NC}"
        return 1
    fi
}

# Final success message
show_success_message() {
    echo -e "\n${GREEN}"
    cat << 'EOF'
   ╔═══════════════════════════════════════╗
   ║        🎉 INSTALLATION COMPLETE! 🎉   ║
   ╚═══════════════════════════════════════╝
EOF
    echo -e "${NC}"
    
    echo -e "${GREEN}✅ Code198x Development Environment is ready!${NC}"
    echo -e "\n${YELLOW}Quick Start:${NC}"
    echo -e "  📁 Create new project: ${BLUE}./scripts/new-project.sh c64 my-game${NC}"
    echo -e "  🔨 Build and run: ${BLUE}cd my-game && ./build.sh${NC}"
    echo -e "  📚 Documentation: ${BLUE}docs/${NC}"
    echo -e "  💻 VS Code setup: ${BLUE}vscode/${NC}"
    
    echo -e "\n${YELLOW}Next Steps:${NC}"
    echo -e "  1. Try the templates in ${BLUE}templates/${NC}"
    echo -e "  2. Read the docs in ${BLUE}docs/${NC}"
    echo -e "  3. Start with Code198x lessons at ${BLUE}https://code198x.com${NC}"
    
    echo -e "\n${BLUE}Happy vintage coding! 🕹️${NC}"
}

# Main installation flow
main() {
    echo -e "${BLUE}🚀 Starting Code198x Development Environment installation...${NC}"
    
    check_prerequisites
    install_package_manager
    install_system_tools
    
    # Install tools for each system
    install_c64_tools
    install_spectrum_tools
    install_amiga_tools
    install_nes_tools
    
    # Create project structure
    create_templates
    create_build_scripts
    create_vscode_integration
    
    # Test everything works
    if test_installation; then
        show_success_message
    else
        echo -e "\n${RED}❌ Installation completed with errors${NC}"
        echo -e "Please check the output above and try again."
        exit 1
    fi
}

# Handle Ctrl+C gracefully
trap 'echo -e "\n${RED}❌ Installation cancelled by user${NC}"; exit 1' INT

# Run main installation
main "$@"