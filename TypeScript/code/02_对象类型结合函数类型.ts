type PointType = { x: number, y: number };

function getPoint(point: PointType) {
  console.log(point.x);
  console.log(point.y);
}

// void 类型使用
type FnType = (name: string) => void
const getName: FnType = (name) => {
  console.log(name);
}


// 联合类型
type MyNumber = string | number
function num(number: MyNumber) {
  console.log(number);
}

