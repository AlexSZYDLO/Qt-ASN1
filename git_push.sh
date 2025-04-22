#!/bin/bash

mv ~/.ssh/gitlab_perso/id_rsa_perso* ~/.ssh/
git push
mv ~/.ssh/id_rsa_perso* ~/.ssh/gitlab_perso/

git push github
