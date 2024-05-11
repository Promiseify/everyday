// 1.ts对作为函数参数的函数 不进行类型校验，参考forEach，map

// 2.函数调用签名

interface IFn {
  desc: string
  (num: number): number
}

const fn: IFn = (num: number): number => {
  return num;
}

fn.desc = "this is only a function";
console.log(fn(123));

// 3.构造签名
class Person {
  constructor(public name: string, public age: number) { };
}

interface IPersonConstructor {
  new(name: string, age: number): Person;
}

let PersonConstructor: IPersonConstructor = Person
let person = new PersonConstructor("tom", 18)
console.log(person);

// 4.可选参数
function introduce(name: string, age?: number): void {
  if (age) {
    console.log(`Hello, i'm ${name}, my age is ${age}`);
  } else {
    console.log(`Hello, i'm ${name}`);
  }
}

introduce("bob");

// 5.函数的重载
// 可以使用联合类型解决吧

function add(arg1: number, arg2: number): number;
function add(arg1: string, arg2: string): string;

function add(arg1: any, arg2: any): any {
  return arg1 + arg2;
}

console.log(add(1, 2));
console.log(add("aa", "bb"));

function add2(arg1: string | number, arg2: string | number): string | number {
  if (typeof arg1 === 'number' && typeof arg2 === 'number') return arg1 + arg2;
  else return arg1 + '' +  arg2;
}
console.log(add2(1, 2));
console.log(add2("aa", "bb"));

export { }