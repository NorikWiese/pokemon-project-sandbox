---
Teil von:
Ort Type:
---
## Suborte
``` base
filters:
  and:
    - file.path.startsWith("Orte/")
    - note["Teil von"] == this.file
views:
  - type: table
    name: Table

```
## Fights
``` base
filters:
  and:
    - file.path.startsWith("Fights/")
    - location == this.file
views:
  - type: table
    name: Table
    order:
      - file.name

```
## Notes

## Encounters
