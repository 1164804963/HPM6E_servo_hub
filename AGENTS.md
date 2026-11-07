# MCU Project and Code Style

## Core Principle: Write Code Developers Can Understand and Take Over

This style is intended for MCU projects led by developers with AI assistance. It applies across different chips, development libraries, and embedded projects. Judge whether a design is appropriate based on the scale, hardware constraints, and development practices of the current MCU project.

The “human touch” here means the practical judgment ordinary MCU developers exercise in their daily work. Developers have limited time and attention. They focus on implementing the current functionality and keeping it running reliably, using approaches they and whoever takes over can easily understand. They then refine the implementation as real requirements and integration results emerge. AI should follow this approach: recognize what needs to be done now and when the implementation is sufficient.

AI has more techniques at its disposal and can easily anticipate many possible extensions, misuses, and failures, adding frameworks, interfaces, and defensive logic for them in advance. Each choice may seem reasonable on its own, but together they can make a simple feature difficult to read. **Being able to anticipate something does not mean it is worth implementing now.** Code complexity should match what the project actually needs to do today.

Developers still need to read the code themselves, work with external devices, run tests, and debug software and hardware together, then use those results to guide further changes. Code readability directly affects whether development can continue. The core of this style is therefore: **design only as much as the current functionality requires, and let the code clearly express how it works so developers can understand it, take it over, and continue modifying it.**

Code also circulates within the team as material for other engineers to learn from, reuse, and port. Readers include colleagues with the relevant MCU development background who were not involved in this implementation or its associated conversations. Consider their reading experience: they should understand the implementation from the code without first reconstructing the discussion between its author and AI.

## Organize the Architecture Around Actual MCU Project Needs

First examine the project's actual functionality, resources, and call relationships, then decide how to organize files and interfaces. Hardware operations, communication handling, and product logic can be separated naturally when they have distinct responsibilities. Small pieces of closely related logic can stay together for continuous reading. Every additional layer should help solve a current problem or reduce the actual effort needed to understand and maintain the code.

A simple module does not need a complete registration, scheduling, lifecycle, callback, or replacement mechanism in advance. If a few fixed calls are enough, write out their sequence directly. Introduce appropriate mechanisms when there are actual needs for multiple tasks, multiple users of a module, or multiple targets. Let complexity grow with real requirements.

Make porting and integration points easy to find. When developers open the relevant initialization or adaptation function, they should see the actual configuration and key operations. Direct use of the current chip's or library's interfaces is acceptable in these locations. Prefer reusing functionality already available in the project, keep necessary connections simple, and avoid rebuilding basic infrastructure merely for structural consistency.

Expose only the interfaces and configuration that current users of a module actually need. Keep internal details where they belong, and state fixed conventions explicitly. Turning every constant, resource, and operation into a configurable option for a use case that has not arisen adds work for current developers.

## Let Functions Directly Express the Work They Perform

A reader should be able to follow a function and understand its process. For example, the relationship between preparing data, starting an operation, waiting for completion, and retrieving the result should be easy to follow. Give the normal execution path the main emphasis, with necessary branches arranged around the relevant steps.

A few related operations can be written directly where they are used. Extract logic into a function when it has a distinct meaning, needs reuse, or would clearly distract from the main flow if expanded inline. Decide whether to split code based on whether it becomes easier to read. Avoid breaking a simple process into a chain of calls that requires repeated navigation to piece together just to keep every function short.

Data relationships should be equally direct. A small set of fixed fields can be assigned individually; sequential data can be handled with a clear loop or copy operation. Readers should easily see where data comes from, how it is processed, and where it ends up. Generic mappings, additional mirrored copies of data, and multiple layers of data access interfaces are worth adding only when they actually reduce work.

Use expressions familiar and natural within the current project. Break expressions into steps if they require repeated mental calculation to understand. Omit parameters, states, and forwarding layers that serve no practical purpose. Measure simplicity by how easy the code is to understand and modify. A few extra lines are often preferable when they make the process clearer.

## Add Defensive Logic in Proportion to Actual Needs

Before adding a check, understand what the current call relationships already guarantee. Once confirmed, conditions such as initialization being complete, arguments coming from fixed internal calls, or capacity being managed in one place can be relied upon. Internal functions do not all need to be designed as public library interfaces that anyone might call in any manner. The same condition does not need repeated validation at every layer.

Focus defensive logic on conditions the current functionality truly depends on and failures that actually affect correctness and stability. For example, handle external data that may exceed buffer capacity or hardware operations with explicit failure results at the appropriate location. Keep the response proportionate to the problem. Avoid letting a simple failure lead to multiple layers of error translation, redundant state, and a complete recovery framework.

There is no need to enumerate and implement every theoretically conceivable edge case that has no practical basis in the current project. In particular, avoid surrounding a few lines of core functionality with extensive hypothetical misuse handling, repeated checks, and compatibility branches. Judge whether a defensive measure belongs by the problem it solves in this project and the reading and maintenance burden it introduces.

When simplifying code, consider the actual process. Retain protocol steps, states, and protections that have a clear purpose. Remove parts that are redundant, ineffective, or prepared solely for hypothetical scenarios. Keeping the main flow clear and handling necessary conditions appropriately are part of the same goal.

## Refine the Project Through Actual Development and Integration

In each iteration, first complete the functionality currently defined, handle known necessary conditions, and verify the result appropriately. Undefined extensions and exception mechanisms without a practical basis can wait until a real requirement arises or testing and integration reveal a problem. Add them in response to the actual circumstances.

Follow the same approach to performance optimization: first understand how execution actually proceeds, then measure where time is spent. Before adopting a more complex technique, confirm that it addresses a current bottleneck and assess the additional configuration, data movement, and call overhead it introduces.

Allowing a project to evolve does not reduce the completeness of its current, explicit requirements. It lets developers understand the implementation at each stage and decide what to do next based on real results, without first having to understand a system prepared for many unknown scenarios.

## Keep Clarity in the Code Itself

Developers should be able to understand the structure, execution flow, and data relationships from the source code and find the places they need to fill in or modify. Interface names, file organization, and comments should support this reading process. Follow clear, familiar practices already used in the project; there is no need for an extensive additional formatting standard.

When colleagues learn or port a feature, they should easily identify its purpose, necessary dependencies, and modification points. Briefly explain key assumptions near the relevant code so whoever takes over can judge which conditions must still hold in another project. Enable reuse primarily through clear responsibilities and integration points, without expanding the implementation into a general framework in advance.

Use short, nearby comments to explain reasons, hardware constraints, and key conventions that the code cannot readily express on its own. Do not compensate for avoidable design complexity with extensive comments or chat explanations. This style also does not require a fixed checklist report after every task. The criterion is always whether the code itself is clear.

After reorganizing or modifying code, also remove obsolete implementations, calls, configuration, and documentation so developers see what is actually in use today. An ordinary MCU developer following this code should understand how it performs its task and feel confident continuing to modify it.

## Concise Instructions for Direct Use with AI

Work according to how ordinary MCU developers actually write and read projects. Focus on the functionality and stability currently required. Use direct, clear implementations with an appropriate level of complexity, making the architecture, functions, and data flow easy to understand. Layers, encapsulation, states, and checks should serve actual current problems. Rely on conditions the project already guarantees reliably, and do not build mechanisms in advance for every possible extension, misuse, or failure.

Let the code itself express the process so I can understand it, find the places to modify, and continue guiding development after testing and software/hardware integration. Also make it easy for colleagues who were not involved in development to learn from, reuse, and port the code. They should identify its purpose, dependencies, and modification points from the code and necessary nearby explanations, without knowing the chat history. Complete the current requirements and allow the project to evolve with actual circumstances. Do not make anticipating everything at once a design objective, and do not use extensive comments, explanations, or fixed reporting formats to compensate for code that is difficult to read. Follow the project's naming and formatting conventions, focusing on design judgment, the main execution flow, and the reading experience.

## Ongoing Applicability

This document applies throughout MCU development in this project. Read it again when starting a new task, or when context compaction or a handoff leaves its full meaning uncertain. Interpret these design choices in the context of the current task; do not mechanically treat them as prohibitions on encapsulation or checks.

Clarity belongs in the source code. No additional style report in a fixed format is required. Follow the user's current explicit requirements for each specific task.
