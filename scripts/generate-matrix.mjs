#!/usr/bin/env node

/**
 * Generate GitHub Actions workflow matrix from systems configuration.
 * This ensures consistency between the configuration and CI/CD pipeline.
 */

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Load systems configuration
function loadSystemsConfig() {
  const configPath = path.join(path.dirname(__dirname), 'systems-config.json');
  const configData = fs.readFileSync(configPath, 'utf8');
  return JSON.parse(configData);
}

// Generate build matrix for GitHub Actions
function generateBuildMatrix(systems) {
  return systems.map(system => ({
    system: system.id,
    assembler: system.assembler,
    'test-file': 'test.asm',
    'test-output': system.test_output,
    'test-command': system.test_command
  }));
}

// Generate verify matrix for GitHub Actions
function generateVerifyMatrix(systems) {
  return systems.map(system => ({
    system: system.id,
    'test-command': system.verify_command,
    'test-output': system.verify_output
  }));
}

// Output matrix in YAML format
function outputYamlMatrix(matrix, matrixName) {
  console.log(`# ${matrixName} matrix configuration`);
  console.log('include:');

  matrix.forEach(entry => {
    console.log(`  - system: ${entry.system}`);
    Object.entries(entry).forEach(([key, value]) => {
      if (key !== 'system') {
        console.log(`    ${key}: ${value}`);
      }
    });
    console.log();
  });
}

// Output matrix in JSON format
function outputJsonMatrix(matrix) {
  console.log(JSON.stringify({ include: matrix }, null, 2));
}

// Generate Docker images table in Markdown
function generateDockerTable(systems) {
  console.log('| System | Docker Image | Pull Command |');
  console.log('|--------|--------------|--------------|');

  systems.forEach(system => {
    const image = `code198x/${system.id}:latest`;
    const pullCmd = `\`docker pull ${image}\``;
    console.log(`| ${system.name} | \`${image}\` | ${pullCmd} |`);
  });
}

// Generate assembler commands for verification script
function generateAssemblerCommands(systems) {
  const assemblers = {};

  systems.forEach(system => {
    assemblers[system.id] = {
      command: system.test_command.replace('test.', ''),
      extension: system.file_extension,
      docker: `docker run --rm -v $(pwd):/workspace code198x/${system.id}:latest`
    };
  });

  console.log('// Assembly commands for each system');
  console.log('const assemblers = ' + JSON.stringify(assemblers, null, 2) + ';');
}

// Main execution
function main() {
  const args = process.argv.slice(2);

  if (args.length === 0) {
    console.log('Usage: generate-matrix.mjs [build|verify|table|json|assemblers]');
    process.exit(1);
  }

  const config = loadSystemsConfig();
  const systems = config.systems;
  const command = args[0];

  switch (command) {
    case 'build':
      outputYamlMatrix(generateBuildMatrix(systems), 'Build');
      break;
    case 'verify':
      outputYamlMatrix(generateVerifyMatrix(systems), 'Verify');
      break;
    case 'table':
      generateDockerTable(systems);
      break;
    case 'json':
      outputJsonMatrix(generateBuildMatrix(systems));
      break;
    case 'assemblers':
      generateAssemblerCommands(systems);
      break;
    default:
      console.error(`Unknown command: ${command}`);
      process.exit(1);
  }
}

// Run if called directly
if (import.meta.url === `file://${process.argv[1]}`) {
  main();
}

export {
  loadSystemsConfig,
  generateBuildMatrix,
  generateVerifyMatrix,
  generateDockerTable
};