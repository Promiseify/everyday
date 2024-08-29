class Printer {
  log(data) {
    console.log(data);
    return this;
  }

  wait(time) {
    return new Promise(resolve => setTimeout(resolve, time * 1000))
  }
}



async function printData() {
  const printer = new Printer();
  await printer.log(1)
    .wait(3)
    .log(2)
    .log(3);
}

printData()