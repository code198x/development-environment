#!/usr/bin/env node

/**
 * Add a new system to the Code198x development environment
 * This creates all necessary files and updates configuration
 */

import fs from 'fs';
import path from 'path';
import readline from 'readline';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function prompt(question) {
  return new Promise((resolve) => {
    rl.question(question, resolve);
  });
}

async function collectSystemInfo() {
  console.log('🎮 Add New System to Code198x Development Environment\n');

  const systemInfo = {};

  systemInfo.id = await prompt('System ID (e.g., atari-2600): ');
  systemInfo.name = await prompt('Full Name (e.g., Atari 2600): ');
  systemInfo.assembler = await prompt('Assembler (e.g., dasm): ');
  systemInfo.assembler_name = await prompt('Assembler Name (e.g., DASM): ');
  systemInfo.cpu = await prompt('CPU Type (e.g., 6502, Z80, 68000): ');
  systemInfo.file_extension = await prompt('Output extension (e.g., .bin, .prg, .tap): ');
  systemInfo.description = await prompt('Description: ');

  return systemInfo;
}

function generateDockerfile(systemInfo) {
  const cpu = systemInfo.cpu.toLowerCase();
  let template = '';

  if (cpu === '6502' || cpu === '6507') {
    template = `# ${systemInfo.assembler_name} for ${systemInfo.name}
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="${systemInfo.assembler_name} assembler for ${systemInfo.name} development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \\
    build-essential \\
    git \\
    curl \\
    && rm -rf /var/lib/apt/lists/*

# TODO: Install ${systemInfo.assembler}
# Add installation commands here

# Create workspace directory
WORKDIR /workspace

# Set assembler as entrypoint
ENTRYPOINT ["${systemInfo.assembler}"]

# Default command shows help
CMD ["--help"]`;
  } else if (cpu === 'z80') {
    template = `# ${systemInfo.assembler_name} for ${systemInfo.name}
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="${systemInfo.assembler_name} assembler for ${systemInfo.name} development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \\
    build-essential \\
    git \\
    cmake \\
    && rm -rf /var/lib/apt/lists/*

# TODO: Install ${systemInfo.assembler}
# Add installation commands here

# Create workspace directory
WORKDIR /workspace

# Set assembler as entrypoint
ENTRYPOINT ["${systemInfo.assembler}"]

# Default command shows help
CMD ["--help"]`;
  } else {
    template = `# ${systemInfo.assembler_name} for ${systemInfo.name}
FROM ubuntu:24.04

LABEL maintainer="code198x"
LABEL description="${systemInfo.assembler_name} assembler for ${systemInfo.name} development"
LABEL version="1.0.0"

# Install build dependencies
RUN apt-get update && apt-get install -y \\
    build-essential \\
    git \\
    curl \\
    && rm -rf /var/lib/apt/lists/*

# TODO: Install ${systemInfo.assembler}
# Add installation commands here

# Create workspace directory
WORKDIR /workspace

# Set assembler as entrypoint
ENTRYPOINT ["${systemInfo.assembler}"]

# Default command shows help
CMD ["--help"]`;
  }

  return template;
}

function generateTestAsm(systemInfo) {
  const cpu = systemInfo.cpu.toLowerCase();

  if (cpu === '6502' || cpu === '6507') {
    return `; Simple ${systemInfo.name} test program
; Tests that ${systemInfo.assembler} assembler is working correctly

    processor 6502
    org $1000

start:
    lda #$00        ; Load 0 into accumulator
    tax             ; Transfer to X
    tay             ; Transfer to Y

loop:
    inx             ; Increment X
    cpx #$10        ; Compare with 16
    bne loop        ; Loop if not equal

    rts             ; Return

    ; TODO: Add ${systemInfo.name}-specific initialization`;
  } else if (cpu === 'z80') {
    return `; Simple ${systemInfo.name} test program
; Tests that ${systemInfo.assembler} assembler is working correctly

    org $8000

start:
    ld a, 0         ; Load 0 into accumulator
    ld b, 16        ; Load counter

loop:
    inc a           ; Increment accumulator
    djnz loop       ; Decrement B and loop if not zero

    ret             ; Return

    ; TODO: Add ${systemInfo.name}-specific initialization`;
  } else if (cpu === '68000') {
    return `; Simple ${systemInfo.name} test program
; Tests that ${systemInfo.assembler} assembler is working correctly

    section code,code

start:
    move.l  #0,d0       ; Clear D0
    move.l  #16,d1      ; Set counter

loop:
    addq.l  #1,d0       ; Increment D0
    subq.l  #1,d1       ; Decrement counter
    bne.s   loop        ; Loop if not zero

    rts                 ; Return

    ; TODO: Add ${systemInfo.name}-specific initialization`;
  } else {
    return `; Simple ${systemInfo.name} test program
; Tests that ${systemInfo.assembler} assembler is working correctly
; TODO: Add test code for ${systemInfo.cpu} CPU

start:
    ; Add test code here

    ; TODO: Add ${systemInfo.name}-specific initialization`;
  }
}

async function createSystemFiles(systemInfo) {
  const systemDir = path.join(path.dirname(__dirname), systemInfo.id);

  // Create directory
  if (!fs.existsSync(systemDir)) {
    fs.mkdirSync(systemDir, { recursive: true });
    console.log(`✓ Created directory: ${systemInfo.id}/`);
  }

  // Create Dockerfile
  const dockerfilePath = path.join(systemDir, 'Dockerfile');
  fs.writeFileSync(dockerfilePath, generateDockerfile(systemInfo));
  console.log(`✓ Created Dockerfile`);

  // Create test.asm
  const testAsmPath = path.join(systemDir, 'test.asm');
  fs.writeFileSync(testAsmPath, generateTestAsm(systemInfo));
  console.log(`✓ Created test.asm`);

  // Create README
  const readmePath = path.join(systemDir, 'README.md');
  const readme = `# ${systemInfo.name} Development Environment

${systemInfo.description}

## Building the Docker Image

\`\`\`bash
docker build -t code198x/${systemInfo.id}:latest .
\`\`\`

## Testing

\`\`\`bash
docker run --rm -v \$(pwd):/workspace code198x/${systemInfo.id}:latest test.asm
\`\`\`

## CPU: ${systemInfo.cpu}
## Assembler: ${systemInfo.assembler_name}
## Output Format: ${systemInfo.file_extension}
`;
  fs.writeFileSync(readmePath, readme);
  console.log(`✓ Created README.md`);
}

function updateSystemsConfig(systemInfo) {
  const configPath = path.join(path.dirname(__dirname), 'systems-config.json');
  const config = JSON.parse(fs.readFileSync(configPath, 'utf8'));

  // Add to systems array
  const newSystem = {
    id: systemInfo.id,
    name: systemInfo.name,
    assembler: systemInfo.assembler,
    assembler_name: systemInfo.assembler_name,
    test_command: `-o test${systemInfo.file_extension} test.asm`,
    test_output: `test${systemInfo.file_extension}`,
    verify_command: `-o verify${systemInfo.file_extension} test.asm`,
    verify_output: `verify${systemInfo.file_extension}`,
    file_extension: systemInfo.file_extension,
    description: systemInfo.description
  };

  config.systems.push(newSystem);

  // Sort systems by ID for consistency
  config.systems.sort((a, b) => a.id.localeCompare(b.id));

  fs.writeFileSync(configPath, JSON.stringify(config, null, 2) + '\n');
  console.log(`✓ Updated systems-config.json`);
}

async function main() {
  try {
    const systemInfo = await collectSystemInfo();

    console.log('\n📝 Creating system files...\n');

    await createSystemFiles(systemInfo);
    updateSystemsConfig(systemInfo);

    console.log(`\n✅ Successfully added ${systemInfo.name}!\n`);
    console.log('Next steps:');
    console.log(`1. Complete the Dockerfile in ${systemInfo.id}/Dockerfile`);
    console.log(`2. Update the test program in ${systemInfo.id}/test.asm`);
    console.log(`3. Build the Docker image: make build-${systemInfo.id}`);
    console.log(`4. Test the assembler: make test-${systemInfo.id}`);
    console.log(`5. Update the GitHub Actions workflow if needed`);

  } catch (error) {
    console.error('Error:', error.message);
    process.exit(1);
  } finally {
    rl.close();
  }
}

main();