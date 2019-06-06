open Css;

let revealAfter =
  style([display(`block), maxHeight(`zero), overflow(`hidden), transition("max-height", ~duration=500)]);

let revealAfterOpen = style([maxHeight(`vw(1000.))]);

[@react.component]
let make = (~before: string, ~after: string, ~className: option(string)=?,
  ~afterRevealText:option(string) = ?, ~beforeRevealText:option(string) = ?) => {
  let (show, setShow) = React.useState(() => false);

  let extraClass = show ? revealAfterOpen : "";
  <div className={"reveal " ++ Js.Option.getWithDefault("", className)}>
    <div key="before" className="reveal-before" dangerouslySetInnerHTML={"__html": before} />
    <div
      key="after"
      className={"reveal-after " ++ revealAfter ++ " " ++ extraClass}
      dangerouslySetInnerHTML={"__html": after}
    />
    <button onClick={_e => setShow(_ => !show)}>
    {
      switch (show) {
        | true => {ReasonReact.string(Js.Option.getWithDefault("", afterRevealText))}
        | false => {ReasonReact.string(Js.Option.getWithDefault(">", beforeRevealText))}
      }
    }
    </button>
  </div>
};
