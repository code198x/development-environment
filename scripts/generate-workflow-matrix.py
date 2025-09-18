#!/usr/bin/env python3
"""
Generate GitHub Actions workflow matrix from systems configuration.
This ensures consistency between the configuration and CI/CD pipeline.
"""

import json
import yaml
import sys
from pathlib import Path

def load_systems_config():
    """Load the systems configuration file."""
    config_path = Path(__file__).parent.parent / 'systems-config.json'
    with open(config_path, 'r') as f:
        return json.load(f)

def generate_build_matrix(systems):
    """Generate the build matrix for GitHub Actions."""
    matrix = []
    for system in systems:
        matrix_entry = {
            'system': system['id'],
            'assembler': system['assembler'],
            'test-file': 'test.asm',
            'test-output': system['test_output'],
            'test-command': system['test_command']
        }
        matrix.append(matrix_entry)
    return matrix

def generate_verify_matrix(systems):
    """Generate the verification matrix for GitHub Actions."""
    matrix = []
    for system in systems:
        matrix_entry = {
            'system': system['id'],
            'test-command': system['verify_command'],
            'test-output': system['verify_output']
        }
        matrix.append(matrix_entry)
    return matrix

def output_yaml_matrix(matrix, matrix_name):
    """Output matrix in YAML format for GitHub Actions."""
    print(f"# {matrix_name} matrix configuration")
    print("include:")
    for entry in matrix:
        print(f"  - system: {entry['system']}")
        for key, value in entry.items():
            if key != 'system':
                print(f"    {key}: {value}")
        print()

def output_json_matrix(matrix):
    """Output matrix in JSON format for use in workflows."""
    print(json.dumps({'include': matrix}, indent=2))

def generate_docker_table(systems):
    """Generate markdown table for Docker images."""
    print("| System | Docker Image | Pull Command |")
    print("|--------|--------------|--------------|")
    for system in systems:
        image = f"code198x/{system['id']}:latest"
        pull_cmd = f"`docker pull {image}`"
        print(f"| {system['name']} | `{image}` | {pull_cmd} |")

def main():
    """Main entry point."""
    if len(sys.argv) < 2:
        print("Usage: generate-workflow-matrix.py [build|verify|table|json]")
        sys.exit(1)

    config = load_systems_config()
    systems = config['systems']

    command = sys.argv[1]

    if command == 'build':
        matrix = generate_build_matrix(systems)
        output_yaml_matrix(matrix, "Build")
    elif command == 'verify':
        matrix = generate_verify_matrix(systems)
        output_yaml_matrix(matrix, "Verify")
    elif command == 'table':
        generate_docker_table(systems)
    elif command == 'json':
        matrix = generate_build_matrix(systems)
        output_json_matrix(matrix)
    else:
        print(f"Unknown command: {command}")
        sys.exit(1)

if __name__ == "__main__":
    main()