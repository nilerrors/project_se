# Print System
# TODO: Try and add more tests
        

## Specification 

| Use-Case                                                     | Priority  |
|--------------------------------------------------------------|:---------:|
| 1: Input                                                     |           |
| Use Case 1.1: Reading printers and jobs                      | REQUIRED  |
| Use Case 1.2: Reading printers and jobs with different types | REQUIRED  |
| Use Case 1.3: Reading scanners and scanning jobs             | REQUIRED  |
| Use Case 1.4: Reading printing costs                         | IMPORTANT |
| 2: Output                                                    |           |
| Use Case 2.1: Simple output (old)                            | REQUIRED  |
| Use Case 2.2: Simple output (new)                            | REQUIRED  |
| Use Case 2.3: Advanced textual output                        | IMPORTANT |
| Use Case 2.4: 3D graphical output                            | IMPORTANT |
| 3: Simulation                                                |           |
| Use Case 3.1: Manual processing (old)                        | REQUIRED  |
| Use Case 3.2: Automated processing (old)                     | IMPORTANT |
| Use Case 3.3: Manual processing met type (new)               | REQUIRED  |
| Use Case 3.4: Automated processing with type (new)           | REQUIRED  |
| Use Case 3.5: Multiple devices with the same type            | REQUIRED  |
| Use Case 3.6: CO2-friendly job scheduling                    | IMPORTANT |
| Use Case 3.7: Tracking CO2 emissions                         | REQUIRED  |
| Use Case 3.8: CO2 compensation                               | IMPORTANT |
| Use Case 3.9: Statistical calculations                       |  USEFUL   |
| 4: User interface                                            |           |
| Use Case 4.1: Admin GUI                                      |  USEFUL   |
| Use Case 4.2: User GUI                                       | IMPORTANT |
| Use Case 4.3: GUI with CO2 emissions overview                |  USEFUL   |


### We gaan de volgende use-cases (op dit moment) implementeren:
- [x] Use Case 1.1
- [x] Use Case 1.2
- [x] Use Case 1.3
- [x] Use Case 1.4
- [x] Use Case 2.1
- [x] Use Case 2.2 <---- (Step 4 niet geïmplementeerd)
- [x] Use Case 2.3 <---- Nieuwe Functie
- [x] Use Case 3.1
- [x] Use Case 3.2
- [x] Use Case 3.3 <---- Assigner Aanpassen
- [x] Use Case 3.4 <---- Assigner Aanpassen
    > Hier moeten we de reports aanpassen. Een aantal beslissingen die nog gemaakt moeten
      worden in het maken van de report.
  1. Jobs die niet assigned kunnen worden, laten zien of weghalen?
     1. gekozen om die weg te halen, want er wordt een message laten zien.
- [x] Use Case 3.5
- [x] Use Case 3.7
