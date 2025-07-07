#!/bin/bash

set -e

COMMIT_MSG=${1:-"Auto commit: $(date '+%Y-%m-%d %H:%M:%S')"}


git add .

git commit -m "$COMMIT_MSG"

git branch -M main
git push -u origin main

git remote remove origin 2>/dev/null || true  # Clean existing remote if exists
git remote add origin https://github.com/arjunsingh4545/splitwiseClone.git

git push -u origin main              # Push to main branch

