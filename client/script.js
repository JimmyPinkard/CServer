console.log("Hello World");

class Header extends HTMLElement
{
    constructor()
    {
        super();
        this.innerHTML = `<header>
        <h1 id="site-title">Hello World</h1>
        <h2 id="page-title">${this.getAttribute("pageTitle")}</h2>
    </header>`;
    }
}
customElements.define("header-component", Header);