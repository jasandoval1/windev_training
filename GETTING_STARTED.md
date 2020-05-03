## Getting Started

This brief guide will walk you through creating a fork of this project so that you may work locally with all of the training materials while retaining the ability to pull in new updates to the curriculum.

### Initial Configuration

Navigate to the repository overview page for the `windows_developer_training` project. At the top of the page, select the `fork` option to create a new fork of the repository.

![Fork](./.img/fork.PNG)

Once you have successfully created your fork of the project, grab a local clone of the repository.

```
> git clone https://git.cybbh.space/path/to/your/fork/windows_developer_training.git Local
```

Change directories into your local clone of the fork. You can verify that, currently, the only remote set for your clone is the fork you just created:

```
> git remote -v
origin  https://git.cybbh.space/path/to/your/fork/windows_developer_training.git (fetch)
origin  https://git.cybbh.space/path/to/your/fork/windows_developer_training.git (push)
```

Now add the original `windows_developer_training` repository as a second remote with the identifier `upstream`:

```
> git remote add upstream https://git.cybbh.space/csd-g/members/projects/windows_developer_training.git
```

Verify that the new remote was added successfully:

```
> git remote -v
origin  https://git.cybbh.space/path/to/your/fork/windows_developer_training.git (fetch)
origin  https://git.cybbh.space/path/to/your/fork/windows_developer_training.git (push)
upstream        https://git.cybbh.space/csd-g/members/projects/windows_developer_training.git (fetch)
upstream        https://git.cybbh.space/csd-g/members/projects/windows_developer_training.git (push)
```

### Pushing Work to Your Fork

Because you cloned your local repository from the forked remote, your default remote is automatically set to the `master` branch on this remote repository (named, by default, `origin`). Therefore, no additional configuration is required to ensure that your local updates are pushed to the correct remote; a simple 

```
> git push
```

will work correctly by default.

**IMPT** Under the current permissions configuration, one additional step is required in order to enable pusing to the `master` branch of your fork. The original `windows_developer_training` repository protects the `master` branch from direct pushes without a merge request. This setting is propagated to your fork of the repository, implying that you in turn will not be able to push directly to the `master` branch of your fork. For forked repositories (in this particular case, at least) this is not the desired behavior, so ensure that you modify this configuration in the project settings for your forked repository after creating the fork. Once this is done, pushing to the remote `master` branch of your fork should work as expected.

### Pulling in Updates

To pull in updates to the training material itself from the original repository, first `fetch` the `master` branch from your `upstream` remote configured above:

```
> git fetch upstream
c:\Dev\Test>git fetch upstream
From https://git.cybbh.space/csd-g/members/projects/windows_developer_training
 * [new branch]      master     -> upstream/master
```

The `master` branch of the original `windows_developer_training` repository is fetched locally as the branch `upstream/master`.

Now checkout the branch of your fork that you want to merge the updates into. For instance, the `master` branch:

```
> git checkout master
```

And finally, merge the updates into your fork's branch:

```
> git merge upstream/master
```

This synchronizes your local fork with the original `windows_developer_training` project. The next time you push to your fork's remote repository, the updates will also be reflected there.