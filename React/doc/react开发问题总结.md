### 1 使用脚手架创建项目

```cmd
create-react-app 项目名称
```

删除不必要的文件保留项目结构如下

![1698674981330](C:\Users\LJ\AppData\Roaming\Typora\typora-user-images\1698674981330.png)

### 2 配置craco

采用craco相当于在vue项目中使用 vue.config.js，可以配置webpack运行时别名，以及依赖加载的预处理包等

```cmd
npm i -D @craco/craco
```

**解决问题：**在react-scripts刚升级到5.0.1时，craco对于这个版本升级是不支持直接安装依赖的，通过在craco的github的issue中发现了开发者对于这个版本还在开发的craco版本，安装采用alpha版本

craco.config.js文件如下，同时也安装了less预处理器

```cmd
npm i -D craco-less
```

```js
const path = require('path')
const CracoLessPlugin = require("craco-less");
const resolve = pathName => path.resolve(__dirname, pathName)

module.exports = {
  // less
  plugins: [{ plugin: CracoLessPlugin }],
  // webpack
  webpack: {
    alias: {
      "@": resolve("src"),
      "components": resolve("src/components"),
      "utils": resolve("src/utils")
    }
  }
}
```

### 3 初始化项目的css文件

采用normalize.css去进行初始化样式文件

```cmd
npm install normalize.css
```

在index.js文件中引用该初始化css文件，同时引用自己定义的初始化文件，可以使用一些项目常用的文字颜色，大小等等

```js
import "normalize.css"
import "@/assets/css/index.less"
```

### 4 配置react-router

```cmd
npm install react-router-dom
```

简单的配置文件如下：

```js
// 懒加载
import React from "react";
import { Navigate } from "react-router-dom";

const Home = React.lazy(() => import("@/views/home"))
const Detail = React.lazy(() => import("@/views/detail"))
const Entire = React.lazy(() => import("@/views/entire"))

const routes = [
  {
    path: "/",
    element: <Navigate to="/home"/>
  },
  {
    path: "/home",
    element: <Home />,
  },
  {
    path: "/detail",
    element: <Detail />,
  },
  {
    path: "/entire",
    element: <Entire />,
  },
]

export default routes;
```

并在index.js中进行加入router：

```js
import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App';

// 配置react路由
import { HashRouter } from "react-router-dom"

import "normalize.css"
import "@/assets/css/index.less"

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <HashRouter>
      <App />
    </HashRouter>
  </React.StrictMode>
);
```

在根组件(App.jsx)中使用routes：

```jsx
import React, { memo } from 'react';
import { useRoutes } from 'react-router-dom';
import routes from '@/router'

const App = memo(() => {
  return (
    <div className='app'>
      <div className="header">header</div>
      <div className="content">
        {useRoutes(routes)}
      </div>
      <div className="footer">footer</div>
    </div>
  )
})

export default App
```

### 5 配置redux

#### 5.1官方推荐使用方式，使用@reduxjs/toolkit

```cmd
npm install @reduxjs/toolkit react-redux
```

创建home模块示例：

```js
import { createSlice } from '@reduxjs/toolkit'

const homeSlice = createSlice({
  name: "home",
  initialState: {
    productList: []
  },
  reducers: {

  }
})

export default homeSlice.reducer
```

store文件下index.js导出示例，引用模块的reducer，然后统一管理

```js
import { configureStore } from '@reduxjs/toolkit'
import homeReducer from './modules/home'
import entireReducer from './modules/entire'

const store = configureStore({
  reducer: {
    home: homeReducer,
    entire: entireReducer
  }
})

export default store
```

#### 5.2传统方式直接使用redux库

因为安装@redux/toolkit时会默认安装redux

文件拆分格式如下：

![1699507605296](C:\Users\LJ\AppData\Roaming\Typora\typora-user-images\1699507605296.png)

reducer.js中的定义规范

```js
const initialState = {
  currentPage: 3
}

function reducer(state = initialState, action) {
  switch(action.type) {

    default: 
      return state
  }
}

export default reducer 
```

#### 5.3关联react和redux，react-redux的使用

- react 与 redux 是没有关系的，redux 支持 react, angular, jQuery, 甚至是javascript
- Redux 与 React 这类库搭配起来更好用
- react-redux 就是 Redux 官方出的用于配合 React 的绑定库
- react-redux 能够使你的 React 组件从 Redux store 中很方便的读取数据， 并且向 store 中分发 actions 更新数据

**React-Redux 中两个重要的成员**

- Provider 这个组件能够使你整个app都能获取到store中的数据
  - Provider 包裹在跟组件的最外层，使所有的子组件都可以拿到 state
  - Provider 接收 store 作为 props，然后通过 context 往下传递，这样react中任何组件都可以通过 context 获取到 store
  - 解决了容器组件可能存在很深的层级，防止一层一层去传递state
- connect 这个方法能够使组件跟 store 来进行关联
  - Provider 内部组件如果想要使用到 state 中的数据，就必须要 connect 进行一层包裹封装（必须要被 connect 进行加强）
  - connect 就是方便我们组件能够获取到 store 中的state

```jsx
import React from 'react';
import ReactDOM from 'react-dom/client';
// 配置react路由
import { HashRouter } from "react-router-dom"
// 配置redux 通过 react-redux使用
import { Provider } from 'react-redux'
import store from './store';

import App from './App';
import "normalize.css"
import "@/assets/css/index.less"

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  // <React.StrictMode>
    <HashRouter>
      {/* 使用Provider包裹，使用store */}
      <Provider store={store}>
        {/* 全局加入Suspense 由于组件进行懒加载，需要一个loading去加载组件 */}
        <React.Suspense fallback={<div>Loading...</div>}>
          <App />
        </React.Suspense>
      </Provider>
    </HashRouter>
  // </React.StrictMode>
);
```

#### 5.4使用redux-thunk

- 我们必须将网络请求的异步代码放到组件的生命周期中来完成； 
- 事实上，网络请求到的数据也属于我们状态管理的一部分，更好的一种方式应该是将其也交给redux来管理； 

#### 5.5安装redux-devtools

### 6 配置网络请求-axios

```cmd
npm install axios
```

配置格式如下

![1699508393282](C:\Users\LJ\AppData\Roaming\Typora\typora-user-images\1699508393282.png)

axios二次封装 index.js文件示例：

```js
import axios from "axios";
import { BASE_URL, TIMEOUT } from './config'

class Request {
  constructor(baseURL, timeout) {
    this.instance = axios.create({
      baseURL,
      timeout
    })

    this.instance.interceptors.response.use(res => {
      return res.data
    }, err => {
      return err
    })
  }

  request(config) {
    return this.instance.request(config)
  }

  get(config) {
    return this.request({ ...config, method: "get" })
  }

  post(config) {
    return this.request({ ...config, method: "post" })
  }
}

const request = new Request(BASE_URL, TIMEOUT)
export default request
```

config.js

```js
export const BASE_URL = "http://codercba.com:1888/airbnb/api"
export const TIMEOUT = 100000
```

在react中测试使用案例

```jsx
import React, { memo, useEffect, useState } from 'react'
import request from '@/services'

const Home = memo(() => {
  // react进行状态管理，否则无法进行页面的重新渲染
  const [highScore, setHighScore] = useState({})

  // 测试网络请求
  useEffect(() => {
    request.get({
      url: "/home/highscore"
    }).then(res => {
      console.log(res);
      setHighScore(res)
    })
  }, [])

  return (
    <div>
      <h2>{highScore.title}</h2>
      <h3>{highScore.subTitle}</h3>
      {/* 两种方式 */}
      {/* 第一种 */}
      {/* {
        highScore.list && <ul>
          {
            highScore.list.map((item, index) => {
              return <li key={item.id}>{item.name}</li>
            })
          }
        </ul>
      } */}
      {/* 第二种 */}
      <ul>
        {
          highScore?.list?.map((item, index) => {
            return <li key={item.id}>{item.name}</li>
          })
        }
      </ul>
    </div>
  )
})

export default Home
```

### 7.安装使用classnames

classnames 简单的说就是一个把多个className链接起来的工具

```js
classNames('foo', 'bar'); // => 'foo bar'
classNames('foo', { bar: true }); // => 'foo bar'
classNames({ 'foo-bar': true }); // => 'foo-bar'
classNames({ 'foo-bar': false }); // => ''
classNames({ foo: true }, { bar: true }); // => 'foo bar'
classNames({ foo: true, bar: true }); // => 'foo bar'

// lots of arguments of various types
classNames('foo', { bar: true, duck: false }, 'baz', { quux: true }); // => 'foo bar baz quux'

// other falsy values are just ignored
classNames(null, false, 'bar', undefined, 0, 1, { baz: null }, ''); // => 'bar 1'
```

开发环境支持 `ES5`，类名也可以动态化：

```js
let buttonType = 'primary';
classNames({ [`btn-${buttonType}`]: true });
```

![1703060744106](C:\Users\LJ\AppData\Roaming\Typora\typora-user-images\1703060744106.png)

