# CONTRIBUTING.md

## Welcome!

Thank you for your interest in contributing to **Andromeda**, an engine made to display the solar system! This project aims to be a simple, educational 3D engine leveraging OpenGL for rendering. Below are the guidelines to help you get started.

## How to Contribute

We welcome contributions in the form of:

- Reporting bugs or issues
- Suggesting new features
- Improving existing code or documentation
- Submitting bug fixes
- Contributing to future goals (listed below)

## Getting Started

### 1. Fork the Repository
- Click the "Fork" button at the top-right corner of the repository page to create a copy of the project in your GitHub account.

### 2. Clone Your Fork
- Clone the repository to your local machine:
  ```bash
  git clone https://github.com/YOUR_USERNAME/andromeda.git
  ```

### 3. Set Up the Project

1. Download [3rdParty](https://drive.google.com/uc?export=download&id=12FWyoT9oNLicftqyYy6T3bgmBVZnht8h) and place the extracted catalog next to the Andromeda source code as follows:
   ```
   path/to/catalog/
       ├── andromeda
       ├── 3rdParty
   ```
2. Build the Andromeda project.

### 4. Create a Branch
- Create a branch for your feature or bugfix:
  ```bash
  git checkout -b feature/your-feature-name
  ```

### 5. Make Your Changes
- Write clean, well-documented code that aligns with the project’s style.

### 6. Test Your Changes
- If applicable, test your changes to ensure they work as intended and don’t break existing functionality.

### 7. Commit Your Changes
- Use clear and descriptive commit messages:
  ```bash
  git add .
  git commit -m "Add feature: Your feature description"
  ```

### 8. Push to Your Fork
- Push your changes to your forked repository:
  ```bash
  git push origin feature/your-feature-name
  ```

### 9. Open a Pull Request
- Navigate to the original repository and click on "New Pull Request."
- Fill out the PR template and describe your changes in detail.

## Future Goals

1. Develop a 3D engine utilizing OpenGL to render the [solar system application](https://github.com/ArturasDruteika/SolarSystem).
2. Implement ray tracing.
3. (In the far, far future) develop the same engine using Vulkan.

## Coding Guidelines

### Code Style
- Follow the [C++ code style guide](https://google.github.io/styleguide/cppguide.html).
- Use meaningful variable and function names.
- Use `m_` prefix for member variables.

### Comments and Documentation
- Use comments to explain complex code.
- Update documentation files if your changes affect the project’s usage.

## Reporting Issues

If you encounter a bug or have a feature request, please open an issue with the following information:

- A clear title and description of the problem or suggestion
- Steps to reproduce the issue, if applicable
- Relevant logs or screenshots
- Your operating system and compiler version (if applicable)

## Notes

At the moment, Andromeda is a learning project and not intended to be an engine for creating games or similar applications.

## Code of Conduct

By participating in this project, you agree to abide by our [Code of Conduct](CODE_OF_CONDUCT.md).

## Need Help?

If you have questions, feel free to open an issue or contact the maintainers directly.

We appreciate your contributions and look forward to building Andromeda with you!

