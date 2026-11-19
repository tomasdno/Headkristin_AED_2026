# Headkristin_AED_2026
Projeto disciplina AED

1. Ligar ao repositório online
No GitHub, abre o teu repositório, clica no botão verde Code, separador HTTPS, e copia o URL. Depois:

git remote add origin https://github.com/tomasdno/Headkristin_AED_2026.git
git remote -v

2. Trabalhar e fazer commits
Trabalhas normalmente. Quando quiseres guardar:

git add .
git commit -m "descrição do que alteraste"

3. Enviar o branch para o GitHub
Na primeira vez, o branch ainda não existe online, por isso:

git push -u origin nome-do-branch

4. Mudar entre branches

git switch main
git switch nome-do-branch

5. Manter o teu branch atualizado com o main
Se os colegas enviarem alterações para o main, traz-as para o teu branch:

git switch main
git pull
git switch nome-do-branch
git merge main

6. Juntar o teu trabalho ao main
Diretamente pelo terminal:

git switch main
git pull
git merge nome-do-branch
git push

7. Apagar o branch depois de juntares (opcional)

git branch -d nome-do-branch
git push origin --delete nome-do-branch

8. Erros comuns
Fiz alterações no main por engano, antes de criar o branch: não faças commit. Corre git switch -c nome-do-branch e as alterações vão contigo para o novo branch.
Já fiz commit no main por engano: cria o branch (git switch -c nome-do-branch), que fica com esse commit, e depois no main faz git switch main e git reset --hard origin/main para o repor igual ao online. Faz isto só se ainda não deste push.
fatal: a branch named ... already exists: o nome já existe. Usa git switch nome-do-branch (sem -c) ou escolhe outro nome.