git checkout --orphan latest_branch
git add -A
git commit -am "cler log"
git branch -D main
git branch -m main
git push -f origin main