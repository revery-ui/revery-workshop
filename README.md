# Workshop Agenda

We'll be building Flappy Bird together with native ReasonML & Revery!

![FlappyRevery2](https://user-images.githubusercontent.com/13532591/57971219-f1e92600-793f-11e9-96ce-8f6fd722e7fb.gif)

### Location

Saturday, May 25th, 2019

Sapient

1:30 PM - 5:30 PM

Register [here](https://checkout.eventlama.com/#/events/reacteurope-2019/tickets/uuid/8b221323-dce6-45e2-b5a1-d7b017e8e480) if you are interested in joining us!

## Pre-requisities

Prior to the workshop, please install the following dependencies:

- npm (6.5 or higher)
- esy (version 0.5.6): `npm install -g esy@0.5.7`
- VSCode + `reason-vscode` extension

- Follow additional platform-specific instructors:
  - Mac: https://github.com/revery-ui/revery/wiki/Building-&-Installing#for-macos-users
  - Linux: https://github.com/revery-ui/revery/wiki/Building-&-Installing#for-macos-users
  - Windows: https://github.com/revery-ui/revery/wiki/Building-&-Installing#for-windows-native

The first-time build can take a while, as the entire compiler toolchain is being built. We recommend cloning the repository and building via:

- `esy install`
- `esy build`
- `esy run` <-- If you see a window pop-up, you're in great shape!

We'll also have a web environment set up, in case you have trouble getting a local environment or editor integration set up:

[Revery Workshop Playground](https://outrunlabs.com/revery/workshop)

If `esy` is working - you can always copy and paste your code from the playground into `8-complete.re` and use `esy run` to test it out.

## Introduction

We'll be starting the workshop with [1-intro.re](1-intro.re), which sets up some `Constants` and `Asset` paths, so you don't have to worry about those details.

If you fall behind, or want to jump ahead, we've split up the workshop into these chunks:

- [1-intro](1-intro.re)
- [2-components](2-components.re)
- [3-world](3-world.re)
- [4-bird](4-bird.re)
- [5-obstacles](5-obstacles.re)
- [6-scoring](6-scoring.re)
- [7-gameplay](7-gameplay.re)
- [8-completed](8-completed.re)

> __NOTE:__ You can run each of these via `esy x`, for example, `esy x 1-intro`.

To get the most out of it, though, we recommend starting with `1-intro` and working with us up to the completed game, without jumping ahead.

### Resources

If you get stuck, we'll be here to help! 

But here's a few resources for getting information, too:

- [Official ReasonML docs](https://reasonml.github.io/docs/en/what-and-why) - description about language features.
- [Revery API docs](https://outrunlabs.com/revery/api) - information about components, hooks, and available APIs.
- [Revery Playground](https://outrunlabs.com/revery/playground) - more examples that might be helpful.

## Agenda

#### Part 1: Setup + Key Concepts

- Build the app with `esy build`
- Run the app with `esy run`
- Try out the interactive playground

- Introduce some important differences coming from the JS world
    - No return keyword
    - Named arguments
    - Pattern matching
    - Module system
    - Lists vs Arrays

- Common errors and gotchas
    - Floating point operators

- Printing values

> EXTRA CREDIT: Show up with your environment set up!

#### Part 2: Our First (Static) Components

We'll move away from a boring blue screen and start adding some life to our app.

- Create a static `<bird />` component
- Add a position prop to our `<bird />
- Create a static `<ground />` component
- Add a text component

> EXTRA CREDIT: Add a `<sky />` component!

#### Part 3: Creating a <world />

We've got some images at this point - but everything is static, there's no life.

We need to liven things up!

- Create a `<world />` element as a container for the other elements.
- Create a module to manage our game's functional `State`
  - Create the `t` type, which defines our state
  - Define `action` that can manipulate our state
  - Create a `reducer`, which takes an action and a state, and returns a new state
  - Define a `Step(float)` action
- Create a Hook
- Add `<Ticker />` component to dispatch
- Print the time

- Add `parallax` to the ground

> EXTRA CREDIT: Switch the bird images to simulate flapping

  Hint:
    - Pass in `time` as a parameter
    - Use the various bird images (bird-01, bird-02) - figure out a way to map the time to a particular image. The `mod` operator may be helpful (ie, `x mod y`).


#### Part 4: Bird state

- Create a `State.Bird` module
- Track the bird position / velocity / acceleration in new module
- Create an initial state for the `Bird`
- Add a `applyGravity` function
- Connect the bird position to the rendering of the `<Bird />` element
- Add a `Flap` action
- Create a `<View onMouseDown />` to dispatch `Flap`
- `isOnGround` helper method

> EXTRA CREDIT: Adjust the bird to rotate up / down based on velocity

  Hint:
    - The `<Image />` element can take a transform, like: `<Image style=Style.[transform([Transform.Rotate(Degrees(45.))])] />`. 

#### Part 5: Obstacles

Still not much of a game! Let's add some obstacles

- Add `Pipe` module with type `t`
- Create Pipe UI
    - 'Block'
    - 'pipe up' / 'pipe down'
- Add 'pipes' to our game state
- Make 'pipes' move

> EXTRA CREDIT: Make pipe height dynamic
>  
> Hint: Will need to add another parameter to the `CreatePipe` variant.

#### Part 6: Scoring & Collision

- Add a `score` property to our `State`
- Detect when crossing a 'Pipe'
    - `willCross` and `willCrossAny` methods on the pipe
- Detect when colliding with a pipe
    - Bird.getRectangle
    - Rectangle.intersects

> EXTRA CREDIT: Add 'padding' to make the collision more forgiving

#### Part 7: Putting it all together:

- Track mode in state
- Implement 'falling' state 
- Implement 'gameover' state

> EXTRA CREDIT: Rotate the bird when falling

#### Part 8: Bonus

- Run native application
- Extra credit

## License

[MIT License](LICENSE)

Revery-quick-start also includes some assets (font files, etc) that have their own licensing terms. For these, see [ThirdPartyLicenses.txt](ThirdPartyLicenses.txt)

Flappy bird assets are from this project: https://github.com/fullstackio/FlappySwift
