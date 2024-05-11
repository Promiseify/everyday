// string, number, null, undefined, ?[], Array<?>, { prop1: ?, prop2: ? }

let nikeName: string = "yxy";

// 数组两种定义方式
let arr1: string[] = ["nihao", "hello"];
let arr2: Array<number> = [12, 34, 56];
let arr3: Array<string> = arr1;

// 对象类型
let obj: { name: string, age: number } = {
  name: "yxy",
  age: 18
};

// 函数参数类型以及返回值类型，返回值类型可以进行类型推导
function sum(num1: number, num2: number): number {
  return num1 + num2;
}

// unknown类型需要进行任何操作都是不合法的，需要进行类型缩小后再使用
let str: unknown = "12345";
if (typeof str === "string") {
  console.log(str.length);
}

// 元组类型
let arr4: [string, number, number] = ["123", 1, 2];

// 联合类型
let a: number | string = 123;
a = "coder";

