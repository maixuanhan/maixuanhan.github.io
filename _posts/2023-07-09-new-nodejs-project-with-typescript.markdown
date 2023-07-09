---
layout: post
title:  "New Nodejs project with typescript"
date:   2023-07-09 12:00:00 +0800
categories: nodejs
--- 
There are many ways to setup your new project source code. You can clone it from a project template repository or generate it from some online tool (such as Stackblitz) but I find that the cleanest way is to generate it by yourself from scratch.

## 1. Create project folder

```sh
mkdir project-name
cd project-name
```

## 2. Init NPM package.json

```sh
npm init -y
```

## 3. Install typescript and the @types/node

```sh
npm install --save-dev typescript
npm install --save-dev @types/node
```

## 4. Generate tsconfig file

```sh
npx tsc --init
```

## 5. Install eslint to control the coding styles

```sh
npm install --save-dev eslint
npx eslint --init
```

## 6. If you use expressjs

```sh
npm install --save express
npm install --save-dev @types/express
```

All of the information can be modified in the generated configuration files.