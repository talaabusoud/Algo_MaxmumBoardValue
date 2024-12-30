# Maximum Board Value

This repository contains the solution to the "Maximum Board Value" problem, implemented using both recursive (divide and conquer) and dynamic programming approaches.

---
## Problem Statement

Given an NxN board where each cell contains an integer value (negative, zero, or positive), a player starts from an arbitrary cell and moves in a series of steps, either **down** or **to the right**. The goal is to maximize the total value collected by the player as they traverse the board and to print the sequence of values that yields this maximum.

---
## Solution Overview

### Part 1: Divide & Conquer
- **Goal:** Recursively calculate the maximum value possible by exploring all valid paths.
- **Approach:** Define a function `f` that returns the optimal value starting from a given cell, depending on board parameters and the movement.

### Part 2: Dynamic Programming
- **Goal:** Optimize the solution by storing intermediate results in a table, avoiding redundant calculations.
- **Approach:** Use a bottom-up strategy to fill a table representing maximum values for each cell and their corresponding paths.

---

## File Structure

- **`src/main.cpp`**: Implementation of the solution.
- **`docs/ALGO-DP-REPORT.pdf`**: Detailed report with explanations, recursion trees, and dependency tables.
- **`docs/board-max-value_description.pdf`**: Problem description and examples.
