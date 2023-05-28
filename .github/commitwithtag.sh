# Script to commit and push with tag
git add -A
git commit -a -m "$2"
git push
git tag "$1"
git push origin "$1"
