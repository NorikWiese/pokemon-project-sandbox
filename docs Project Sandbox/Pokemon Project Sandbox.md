## Global Choices
``` base
filters:
  and:
    - file.path.startsWith("Global")
views:
  - type: table
    name: Table

```
## Fights
``` base
filters:
  and:
    - file.path.startsWith("Fights/")
views:
  - type: table
    name: Table
    order:
      - file.name
      - Trainer Type
      - Main Type
      - Location
      - note.note

```
## Orte
``` base
filters:
  and:
    - file.path.startsWith("Orte/")
views:
  - type: table
    name: Table
    order:
      - file.name
      - Ort Type
      - Teil von
    columnSize:
      file.name: 204
      note.Ort Type: 233

```
## Other Notes
``` base
filters:
  and:
    - file.path.startsWith("Other")
views:
  - type: table
    name: Table

```
