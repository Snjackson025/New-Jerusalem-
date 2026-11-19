# NEW JERUSALEM AI — Workflow

## What it does

`.github/workflows/newjerusalem.yml` runs on every push and pull request
to `main` that touches `newjerusalem.cpp`, `scripts/newjerusalem-check.sh`,
or the workflow file itself.

It compiles the program with:

```
g++ -std=c++17 -Wall -Wextra -o newjerusalem newjerusalem.cpp
```

Then it runs three smoke tests:

1. **Start up and shut down** — the menu shows, all engines report
   Active, and the program shuts down cleanly.
2. **System status** — option 11 reports 0 knowledge records and all
   six engines (Knowledge, Inquiry, Reasoning, Reflection, Chronology,
   Character) Active.
3. **Add knowledge and search for it** — adds a record (History / Test
   Record) and finds it again with a search for "test".

## Running the checks locally

```
bash scripts/newjerusalem-check.sh
```

The script compiles the program, runs the same three smoke tests in a
temporary directory (so the runtime files `newjerusalem_*.txt` are not
left in the repo), and reports success or failure.

## Note

The workflow file itself cannot be pushed by Muse — the Muse GitHub App
does not have permission to create `.github/workflows/*` files via the
API. It has to be added manually through the GitHub web UI, the same as
FoxMail, CALL-VARS, OmniWeaver, and Ascension.
