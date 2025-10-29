# Contributing to JC3248W535 Driver

Thank you for your interest in contributing! This document provides guidelines for contributing to this project.

## How to Contribute

### Reporting Issues

If you find a bug or have a suggestion:

1. Check if the issue already exists in [Issues](https://github.com/yourusername/JC3248W535-Driver/issues)
2. If not, create a new issue with:
   - Clear, descriptive title
   - Detailed description of the problem or suggestion
   - Steps to reproduce (for bugs)
   - Expected vs actual behavior
   - Hardware and software versions
   - Code samples if relevant

### Submitting Pull Requests

1. **Fork the repository**
   ```bash
   git clone https://github.com/yourusername/JC3248W535-Driver.git
   cd JC3248W535-Driver
   ```

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make your changes**
   - Keep code clean and well-documented
   - Follow existing code style
   - Add comments where necessary
   - Update documentation if needed

4. **Test your changes**
   - Test on real hardware if possible
   - Ensure examples still work
   - Check for compilation errors

5. **Commit your changes**
   ```bash
   git add .
   git commit -m "Add: brief description of changes"
   ```

6. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create a Pull Request**
   - Go to the original repository
   - Click "New Pull Request"
   - Select your branch
   - Describe your changes clearly

## Code Style Guidelines

### General
- Use clear, descriptive variable and function names
- Keep functions focused and concise
- Add comments for complex logic
- Use consistent indentation (2 or 4 spaces)

### C++ Specific
- Use `camelCase` for variables and functions
- Use `PascalCase` for classes
- Use `UPPER_CASE` for constants
- Prefer `const` over `#define` where appropriate

### Example
```cpp
// Good
const int buttonWidth = 100;
void drawButton(int x, int y) {
  // Implementation
}

// Avoid
#define BUTTON_WIDTH 100
void draw_button(int x, int y) {
  // Implementation
}
```

## Documentation

- Update README.md if adding new features
- Add comments to public API functions
- Include examples for new functionality
- Keep documentation clear and concise

## Testing

Before submitting:

- [ ] Code compiles without errors
- [ ] Code compiles without warnings
- [ ] Examples work on hardware
- [ ] No memory leaks
- [ ] Documentation is updated

## What to Contribute

We welcome contributions in these areas:

### Code
- Bug fixes
- Performance improvements
- New features (discuss first in Issues)
- Code optimization
- Better error handling

### Documentation
- Fixing typos
- Improving clarity
- Adding examples
- Translating documentation

### Examples
- New example sketches
- Improved existing examples
- Real-world use cases

### Hardware Support
- Testing on different hardware variants
- Compatibility improvements
- Hardware documentation

## Questions?

Feel free to:
- Open an issue for questions
- Start a discussion in [Discussions](https://github.com/yourusername/JC3248W535-Driver/discussions)
- Contact the maintainers

## Code of Conduct

- Be respectful and inclusive
- Welcome newcomers
- Focus on constructive feedback
- Help others learn

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing! 🎉
