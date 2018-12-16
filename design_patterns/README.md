### Factory

- a static method (creates objects)
- a common method (creates objects with respect to current object state)
  - prototype
- a different class for creating objects of another class
  - builder
  - config
  - factory "method"
  - abstract factory

### Customization point
- behavioural
  - Strategy - *single hierarchy (just a customization point)*
  - Command - *multiple users (independent stateful object with an action)*
- structural
  - Brigde - *multiple hierarcies (abstraction and implementation can be changed independedly)*

### Decorator/Proxy difference

- Decorator
  - does not control wrapee's lifetime
  - does not control flow
- Proxy
  - controls wrapee's lifetime
  - controls flow

### Decorator/Composite difference

- Decorator
  - one wrapee
  - enhances the wrapee's result
- Composite
  - many wrapees
  - sums-up wrapees' results

### Decorator/Chain difference

- Decorator
  - just add additional functionality (pre/post-effects)
- Chain of Responsibility
  - controls flow (pass/interrupt)
