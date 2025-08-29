# Philosophers Simulation in C

This project simulates the **classical Dining Philosophers problem** using **threads in C** and a **Makefile**.  

It demonstrates:

- Thread synchronization  
- Deadlock prevention  
- Timing and concurrency management  

---

## 🛠 Installation

Use the included **Makefile** to build and manage the project:

```bash
make        # Build all object files and executable
make run    # Build executable and clean object files
make clean  # Remove object files
make fclean # Remove objects and executable
make re     # Clean + build fresh executable
```
---
## 
🚀 Usage

Run the program with the following arguments:
```bash
./philosophers <number_of_philosophers> <time_to_death_ms> <time_eating_ms> <time_sleeping_ms> [number_of_meals]
```

