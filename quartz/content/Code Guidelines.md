---
title: Code Guidelines
date: 2025-02-01
description: "Some guidelines to follow when writing code"
tags:
  - guide
---

To write good code we must follow a few basic steps to ensure cohesion across all different branches.

## Naming Convention
Naming convention isn't terribly important, but agreeing on something will make the code more readable.
### Naming Files
By default you should you the dash (-) naming convention. For example, in a file called: `main program` you should call it: `main-program`.
### Naming Variables
You should name variables using the camelCase, which capitalizes all words except the first one, like so: `thisIsCamelCase`
### Naming Commits
The naming convention, is loosely based on: [Conventional Commits v1.0](https://www.conventionalcommits.org/en/v1.0.0/).

The name of your commits should be short (< 10 words) and descriptive. 

Before the message you should add the type of commit and, optionally, the scope, in brakets.

There are 2 types of commit:
- `fix`: When fixing a bug
- `feat`: When adding a new feature or content

The scope is the general are of the code that you have improved, and should be 1 singular word. Examples include: `movement`, `pathfinding`, `sensors`, ...

Examples of commit titles:
- `feat(pathfinding): added 2d mapping`
- `fix(sensors): prevent duplicate entries`
