open Revery;

let render = elem => {
	let init = app => {
			let createOptions =
					WindowCreateOptions.create(
							~width=800,
							~height=600,
							(),
					);
			let win = App.createWindow(~createOptions, app, "FlappyRevery");

			let _: UI.renderFunction = UI.start(win, elem);
	};

	App.start(init);
};
