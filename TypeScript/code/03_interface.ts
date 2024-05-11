// interface用来定义对象类型

interface ICoder {
  name: string,
  coding: (number: number) => void
}

interface IPerson {
  name: string,
  age: number
}

// 交叉类型(&)
const person: ICoder & IPerson = {
  name: "coder",
  age: 18,
  coding(number) {
    console.log("coding code number", number);
  }
}

console.log(person);