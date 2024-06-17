const obj = {
  name: "coderyxy",
  foo: function () {
    console.log(this.name);
  }
}

obj.foo()


// noImplicitThis: true 不能进行上下文推导时会报错
// this 无法进行类型推导出来 所以会报错
// function foo() {
//   console.log(this);
// }

// 规定this的类型
function foo(this: { name: string }, info: { name: string }) {
  console.log("this: ", this);
  console.log("info: ", info);
}

foo.apply({ name: "123" }, [{ name: "33" }])

export { }
