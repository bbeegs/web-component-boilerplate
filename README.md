# web-component-boilerplate

This script produces boilerplate html, javascript and css for an html web component.<br>
It assumes the user will use a html template, it extends the HTMElement, and adds all<br>
the life-cycle hooks to the js.

#### Example usage:
```d
./comp-gen my.custom.comp MyCustomComp my-custom-comp
```

## Output:
3 files:<br>
my.custom.comp.html, my.custom.comp.js, my.custom.comp.css

### my.custom.comp.html
```html
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title></title>
</head>
<body>
<my-custom-comp></my-custom-comp>
<template id="my-custom-comp">
	<link rel="stylesheet" href="./my.custom.comp.css">
</template>
</body>
</html>
```
### my.custom.comp.js
```javascript
'use strict'
class MyCustomComp extends HTMLElement {
	constructor() {
		super();
		const shadow = this.attachShadow({ mode: "open" });
		const template = document.getElementById('my-custom-comp');
		const content = template.content.cloneNode(true);
		shadow.appendChild(content);
	}

	connectedCallback() {

	}

	disconnectedCallback() {

	}

	attributeChangedCallback(name, oldValue, newValue) {

	}

	adoptedCallback() {

	}

}

window.customElements.define('my-custom-comp', MyCustomComp);
```
### my.custom.comp.css
```css
:host{}
```
That's about all I got to say about that. :smile:
