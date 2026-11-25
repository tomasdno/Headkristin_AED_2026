# Guia de Workflow Git

Guia rápido com os comandos e boas práticas a seguir sempre que fores trabalhar no projeto.

> **Nota:** Substitui `teu-branch` pelo nome real do teu branch em todos os comandos abaixo.

---

## 1 e 2. Atualizar o teu branch com a `main` e trazer tudo para o PC

Antes de começares a escrever código, garante que estás no teu branch, atualizado com o que está online e com as novidades da `main`:

```bash
git checkout teu-branch
git fetch origin
git pull origin teu-branch
git merge origin/main
```

*Se aparecerem conflitos no `git merge`, resolve-os no teu editor de código, faz `git add .` e `git commit` antes de começares a trabalhar.*

---

## 3. Guardar o trabalho quando acabares (Commit)

Depois de editares os ficheiros no PC:

```bash
git status
git add .
git commit -m "Descreve aqui de forma curta o que fizeste"
```

---

## 4. Enviar o teu branch do PC para o repositório online

```bash
git push origin teu-branch
```

---

## 5. Fazer merge do teu branch online com a `main` online

Escolhe uma das duas opções abaixo, consoante trabalhes em equipa ou sozinho:

### Opção A — Via Site (Recomendado em equipa)
1. Vai ao repositório online (GitHub / GitLab).
2. Abre um **Pull Request (PR)** (ou *Merge Request*) do `teu-branch` para a `main`.
3. Revê as alterações e clica em **Merge**.

### Opção B — Via Linha de Comandos (Mais rápido se trabalhares sozinho)
```bash
git checkout main
git pull origin main
git merge teu-branch
git push origin main
git checkout teu-branch
```
*(O último comando volta logo para o `teu-branch` para evitares programar diretamente na `main` por acidente da próxima vez).*

---

## Boas Práticas no Dia a Dia

* **Usa `git status` frequentemente:** Antes de qualquer `add`, `commit` ou `checkout`, confirma sempre em que branch estás e que ficheiros alteraste.
* **Commits pequenos e frequentes:** Em vez de um único commit gigante no fim do dia, faz um commit por cada funcionalidade ou correção concluída. Se algo correr mal, é muito mais fácil voltar atrás.
* **Nunca programes diretamente na `main`:** Mantém a `main` sempre funcional e estável.
* **Sincroniza antes de fazer merge:** Se demoraste muito tempo a trabalhar e outra pessoa atualizou a `main` entretanto, repete o `git fetch origin` e `git merge origin/main` antes do passo 5 para resolveres eventuais conflitos no teu branch e não na `main`.