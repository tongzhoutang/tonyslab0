25800190006 唐同舟
1. 
  我之前有过多人协调开发的经历。我们通过线下会议、使用共享文档工具、网盘下载、群发文件（甚至U盘拷贝）等传统原始的手段实现分工协作。While Git and GitHub have brought a wind of change.
  文件有三种状态：已修改（modified）、已暂存（staged）、已提交（committed）。暂存区的正式名字叫 index，它是 .git 目录里的一个文件，记录的是"下一次提交会是什么样子"。

	分成两步的好处：

	a. 可以只提交一部分改动。 你可能一口气改了很多地方，比如修了一个 bug，顺手调了样式，还有一个功能写到一半。暂存区让你只 add 修 bug 的那部分，先提交成一个干净的提交，剩下的以后再说。用 git add -p 甚至能按"代码块"挑选，同一个文件里的改动也能拆开提交。
	一个提交只做一件事。 这样历史更好读。以后要 revert 或排查"哪次提交引入了 bug"时，粒度小的提交很容易定位和撤销。
	b. 提交前有检查的机会。 先 add，再用 git diff --staged 确认"这次到底会提交什么"，最后才 commit。暂存区相当于提交前的预览和草稿。
	没写完的东西不会被带进去。 调试用的 print、临时文件，只要不 add 就不会进入提交。

| 命令            | 列出的内容<br>                   |
| ------------- | --------------------------- |
| git branch    | 只列本地分支，当前分支前面标 *            |
| git branch -r | 只列远程跟踪分支（如 origin/main）<br> |
| git branch -a | 本地分支和远程跟踪分支都列出来（all）        |
参考：Git 官方文档（[git-branch](https://git-scm.com/docs/git-branch)）和《Pro Git》第 1.3 节（[What is Git](https://git-scm.com/book/zh/v2/起步-Git-是什么%3F)）

3.  三篇文章都读了。
###### A. 文章概括
Commit Message 规范（阮一峰）

这篇介绍的是业界最常用的 **Angular 规范**。它的思路是：提交说明也要像代码一样有固定格式。

- **结构**：分为 Header、Body、Footer 三段，只有 Header 必填。
- **Header** 的格式是 `type(scope): subject`：
    - `type` 表示提交的类型，常用的有 `feat`（新功能）、`fix`（修 bug）、`docs`（文档）、`style`（格式）、`refactor`（重构）、`test`（测试）、`chore`（构建或工具相关）。
    - `scope` 表示影响范围，可以不写。
    - `subject` 是一句简短描述，以动词开头，不加句号。
- **Body** 写这次改动的动机，以及和原来的行为有什么不同。
- **Footer** 用来标注不兼容改动（`BREAKING CHANGE`）或关闭 Issue（`Closes #123`）。
- **好处**：历史记录更容易浏览和筛选，还能**自动生成 Changelog**（版本更新日志）。配套工具有 Commitizen（交互式填写）、validate-commit-msg（检查格式）、conventional-changelog（生成日志）。

示例：`feat(login): 添加验证码校验`


Git Flow 分支控制

这是一套**分支管理模型**，规定每种分支的用途、从哪里创建、合并到哪里。

|分支|用途|从哪来|合到哪去|
|---|---|---|---|
|`master`|线上稳定版本，每次发布打 tag|—|长期存在|
|`develop`|日常开发的公共分支|master|长期存在|
|`feature/*`|开发新功能|develop|develop，合并后删除|
|`release/*`|发布前的测试和准备|develop|master 和 develop|
|`hotfix/*`|线上紧急修复|master|master 和 develop|

- 核心原则是**"从哪里来，就回到哪里去"**。
- 合并时统一加 `--no-ff`，保留分支的合并痕迹。
- 可以直接用原生 Git 命令操作，也可以用 git-flow 扩展工具简化步骤。


 语义化版本 SemVer

这是一套给版本号**赋予明确含义**的规范，格式为 `主版本号.次版本号.修订号`（X.Y.Z）：

- **主版本号**：有不兼容的 API 修改时加一，例如 `1.4.2 → 2.0.0`。
- **次版本号**：新增功能、但保持向下兼容时加一，例如 `1.4.2 → 1.5.0`。
- **修订号**：只修 bug、保持向下兼容时加一，例如 `1.4.2 → 1.4.3`。
- `0.y.z` 表示处于初始开发阶段，随时可能变化。软件稳定、开始被别人依赖时，就应该发布 `1.0.0`。
- 还可以加扩展标记：`-alpha.1` 表示先行版本，`+build.5` 表示编译元数据。
- **要解决的问题**是"依赖地狱"：依赖的库一升级，你的项目就可能出错。有了规范，只看版本号就能判断升级是否安全。


**三者的联系**

这三篇其实讲的是同一条链路上的三个环节：

- **Commit 规范**让每次提交都带上类型标签。
- **Git Flow** 决定这些提交在哪个分支上产生、如何流转，以及什么时候发布。
- **SemVer** 决定发布时版本号怎么升：有 `BREAKING CHANGE` 升主版本，有 `feat` 升次版本，只有 `fix` 升修订号。

所以这三者配合起来，可以做到"写好提交 → 自动算出版本号 → 自动生成更新日志"。semantic-release 这类工具就是这样工作的。

###### B. 我对"为什么要学习 Git"的理解

我觉得可以分成三个层次。

**1. 对自己：让试错变得便宜。**  
没有版本控制时，大家会复制出 `final.py`、`final2.py`、`真的final.py`，改坏了也回不去。有了 Git，每次提交都是一个可以回退的存档点，所以你敢大胆重构，也敢去试一个不确定的想法：开个分支，试错了删掉就行。**这种安全感直接影响写代码的效率和胆量。**

**2. 对团队：Git 是协作的基础。**  
多人同时改同一个项目，靠发压缩包或网盘同步必然会互相覆盖。Git 的分支、合并、冲突处理和 Pull Request 机制，是"多人写同一份代码"这件事的底层支撑。上面三篇文章讲的规范，也都是建立在 Git 之上的**团队约定**：提交怎么写、分支怎么分、版本怎么发。只会 `add/commit/push` 只能算能用；理解这些约定，才能真正融入一个团队或开源社区。

**3. 对长期发展：Git 是开发者的通用基础设施。**

- 几乎所有公司和开源项目都用 Git，它和会用命令行一样，是默认要求的技能。
- GitHub 上的提交记录和项目，本身就是一份公开的作品集。
- CI/CD（自动测试、自动部署）、代码审查、Issue 管理、自动发版，这些现代开发流程都挂在 Git 上。
- 读开源项目的提交历史，是学习别人为什么这样写代码的好材料。规范的 commit message 让这些历史真正读得懂。

综上，Git 表面上是一个保存代码的工具，实际上它记录了一个项目是怎么一步步演变过来的。学 Git 学的不只是命令，还有管理变化和与人协作的方法。


5. 
###### 实验步骤记录
1) 在clone库时遇到报错 `fatal: unable to access 'https://github.com/tongzhoutang/tonyslab0.git/': Failed to connect to github.com:443 after 21106 ms: Could not connect to server`
2) 重设SSH私钥、公钥，成功clone
3) 修改main.c，运行，commit
4) 创建分支feature，分别在main和feature同一位置修改字段制造冲突
5) 尝试merge，报告conflict
6) 两者皆保留，消conflict，成功merge
7) 总结并撰写实验报告
8) commit and push everything

###### Appendix: Screenshots
aha-conflict.png
![[aha-conflict.png]]
conflict-resolved.png
![[conflict-resolved.png]]
merge-complete.png
![[merge-complete.png]]

###### Appendix: Suggestions
Dear TAs,

If you can upload upcoming lab pages to the website, it would be convenient for us to **preview** (or even do something in advance), so that we can design a more compact and efficient agenda in busy semesters (like this one).

Good job and thanks for your dedication!