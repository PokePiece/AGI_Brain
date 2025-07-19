# AGI_Brain

A C-based modular brain simulation framework integrated with Python for LLM management.

## Overview

This project implements a modular brain architecture with neurons and connections in C, serving as the base layer controlling brain structure and dynamics. It interfaces with Python to manage large language models (LLMs) for advanced automation and language tasks.

The system architecture allows:

- Creation of neurons with unique IDs
- Directed connections between neurons with weighted links
- Brain update cycles simulating neuron firing and spike propagation
- Integration with a Python LLM module for AI-driven capabilities

Future extensions will add interfaces to:

- **Lisp** for meta-cognition and symbolic reasoning  
- **Prolog** for formal logic and deductive inference  
- **R** for micro-neuronic management and data-driven analytics  

## Building

This project uses CMake.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

The compiled executable runs a CLI that:

Simulates neuron updates and firing

Calls the Python LLM module for language generation and reasoning

Make sure the Python environment and dependencies are installed and accessible.

## Dependencies

C compiler (GCC, Clang, MSVC)

Python 3.8+

Python packages listed in requirements.txt

## Notes

The Python module is packaged separately and called via subprocess from C.

To distribute the project as a standalone app, package both the compiled C executable and the Python module with its dependencies.