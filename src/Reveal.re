open ReasonReact;
open Css;

let revealAfter =
  style([display(`block), maxHeight(`zero), overflow(`hidden), transition("max-height", ~duration=500)]);

let revealAfterOpen = style([maxHeight(`vw(1000.))]);

type state = {show: bool};

type action =
  | Setshow(bool);

let changeText = (status: bool, afterRevealText:option(string), beforeRevealText:option(string)) =>
  status ?
    Js.Option.getWithDefault("", afterRevealText) :
    Js.Option.getWithDefault(">", beforeRevealText);

let component = ReasonReact.reducerComponent("RevealRe");

let make = (~before: string, ~after: string, ~className: option(string)=?,
  ~afterRevealText:option(string) = ?, ~beforeRevealText:option(string) = ?, _children) => {
  ...component,
  initialState: () => {show: false},
  reducer: (action, _) =>
    switch (action) {
    | Setshow(show) => Update({show: show})
    },
  render: self => {
    let extraClass = self.state.show ? revealAfterOpen : "";
    <div className={"reveal " ++ Js.Option.getWithDefault("", className)}>
      <div key="before" className="reveal-before" dangerouslySetInnerHTML={"__html": before} />
      <div
        key="after"
        className={"reveal-after " ++ revealAfter ++ " " ++ extraClass}
        dangerouslySetInnerHTML={"__html": after}
      />
      <button onClick={_e => self.send(Setshow(!self.state.show))}>
        {ReasonReact.string(changeText(self.state.show, afterRevealText, beforeRevealText))}
      </button>
    </div>;
  },
};
