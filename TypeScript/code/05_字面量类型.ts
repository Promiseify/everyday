
// 字面量类型
type Direction = "top" | "bottom" | "left" | "right";
const direction: Direction = "top";

// 使用 as const 将对象字面量声明为只读的字面量类型。这意味着无法对对象中的属性进行修改。
const info = { d: "top" } as const;
// 报错
// info.d = "right";

type DirectionType = (d: Direction) => Direction  
const getDirection: DirectionType = (d) => {
  return d;
}

console.log(getDirection(info.d));

export {}