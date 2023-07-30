# Contributing

Is there a feature you'd like to see, or a bug you've encountered? Please let us know, and help us make _It Depends_ great for everyone! Or, if you're a developer, try to fix it yourself! If you'd like to contribute back to _It Depends_ but you're not quite sure yet what you can add, take a look at the [roadmap](#12-roadmap).

All contributions are welcome, so feel free to join the open source community and support _It Depends_ through your expertise!

To make sure everyone can contribute to _It Depends_ we value the quality and understandability of our code and repository.
So when you're building a feature, or patching a bug and you've made a decision, please document that decision in the [`docs/design.md`](docs/design.md) document. This will help future contributors to understand your rationale. If you've updated some logic in the code, please check the decision records and update the related onces. If you've done all this, update the test-suite and validate that your newly created code does exactly what you'd documented.

## 1 Branching strategy

So now that your idea is implemented, documented and tested it's time to merge it into _It Depends_! To help you out a bit on how to setup a branch, we've got you covered in this chapter!

_It Depends_ does not use a development branch but instead uses short lived feature branches which are directly merged into the `main`-branch. We've chosen this strategy 'cause we believe in _release often, release fast_. There's no need for your feature to gather dust in a stale `development` branch while waiting on some arbitrary date to be released. But, we do however, have some guidelines:

- If you're contributing a __feature__ use the `feature/<your-feature-name>` naming convention
- If you're contributing a __bug fix__ use the `bugfix/<the-name-of-the-bug>` naming convention.
- If you're contributing to __documentation__ use the `documentation/<name-of-change>` naming convention.
- If you're contributing a __hot fix__ use the `hotfix/<hotfix-type>-<name>` naming convention
    - These can be useful for updating dependency versions

# Create a new release

To create a new release of _It Depends_, edit the `CmakeLists.txt` file and update the `VERSION` parameter of the `project` function. For versioning _It Depends_ uses
semantic versioning. Which, given the documentation on [semver.org](https://semver.org), means that the version number consists of MAJOR.MINOR.PATCH.

When creating a release of _It Depends_, check what kind of changes have been applied since the previous version and categorize these in one of the following segments:

1. Incompatible API change, or a user interface change
2. New functionality which doesn't break existing functionality
3. Bug fix

These can be mapped on the semantic versioning scheme in the following ways:

* Update the __MAJOR__ version when you've made a __breaking change__ either in the interfaces or in the UI.
* Update the __MINOR__ version when a __new feature__ is introduced
* Update the __PATCH__ version when a __bug is resolved__

When you've updated the version in `CMakeLists.txt` create a new tag in Git using the
following structure: `MAJOR.MINOR.PATCH`. For version 5 with a bugfix this would be `v5.0.1`.

This can be created using the following Git-command:

```bash
$ git tag -a v5.0.1
$ git push -u origin v5.0.1
```

This will create the tag locally and then push it to Github which in turn will kick off the required
pipelines to create the new release and add the build artifacts.