#!/usr/bin/env bash
# Local check mirroring .github/workflows/newjerusalem.yml.
# Usage: bash scripts/newjerusalem-check.sh
# Runs in a temp directory so the runtime files
# (newjerusalem_*.txt) do not pollute the repo.
set -euo pipefail

cd "$(dirname "$0")/.."

workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT
g++ -std=c++17 -Wall -Wextra -o "$workdir/newjerusalem" newjerusalem.cpp
cd "$workdir"

echo "Test 1: start up and shut down"
output=$(printf '0\n' | ./newjerusalem)
echo "$output" | grep -q "NEW JERUSALEM AI"
echo "$output" | grep -q "Pursue truth, preserve knowledge"
echo "$output" | grep -q "New Jerusalem AI shutting down."

echo "Test 2: system status"
output=$(printf '11\n\n0\n' | ./newjerusalem)
echo "$output" | grep -q "Knowledge records: 0"
echo "$output" | grep -q "Inquiry engine: Active"
echo "$output" | grep -q "Chronology engine: Active"

echo "Test 3: add knowledge and search for it"
output=$(printf '1\nHistory\nTest Record\nTest knowledge entry\n\n3\ntest\n\n0\n' | ./newjerusalem)
echo "$output" | grep -q "Knowledge record saved. ID: 1"
echo "$output" | grep -q "Test Record"

echo "All NEW JERUSALEM checks passed."
