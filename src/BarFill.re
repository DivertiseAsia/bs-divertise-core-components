[@bs.config {jsx: 3}];
open ReasonReact;

let optElement = (className, opt) =>
  switch (opt) {
  | None => null
  | Some(el) => <div className> el </div>
  };

let fillTextElement = opt =>
  switch (opt) {
  | None => null
  | Some(text) => <span className="fill-text"> {text |> string} </span>
  };

[@react.component]
let make =
    (
      ~percent: int,
      ~className: option(string)=?,
      ~onClick=?,
      ~title: option(string)=?,
      ~fillText: option(string)=?,
      ~dropElement: option(React.element)=?,
      ~topLeft: option(React.element)=?,
      ~topRight: option(React.element)=?,
      ~belowLeft: option(React.element)=?,
      ~belowRight: option(React.element)=?,
    ) => {
  <div ?className>
    <div className="d-flex justify-content-between">
      {topLeft |> optElement("top-left text-left -font-light-grey")}
      {topRight |> optElement("top-right -text-right font-weight-bold")}
    </div>
    <div
      ?title
      ?onClick
      className={
        "progress "
        ++ Js.Option.getWithDefault("progress-default", className)
      }>
      <div
        className="fillbar"
        style={
          ReactDOMRe.Style.make(~width=string_of_int(percent) ++ "%", ())
        }>
        {fillTextElement(fillText)}
        {dropElement |> optElement("drop-fill")}
      </div>
    </div>
    {belowLeft |> optElement("below-left text-left")}
    {belowRight |> optElement("below-right text-right")}
  </div>
};