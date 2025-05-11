const http = require("http");
const fs = require("fs");
const { execSync } = require("child_process");

const html = (x, y, z, image) => `
<!DOCTYPE html>
<html>
  <body>
  <script>
  window.addEventListener("load", () => {
    const params = new URLSearchParams(window.location.search)
    const x = params.get("x")
    const y = params.get("y")
    const z = params.get("z")

    document.querySelector("#x").value = x
    document.querySelector("#y").value = y
    document.querySelector("#z").value = z

    document.querySelector("#render").addEventListener("click", () => {
      const url = new URL(window.location.href);
      url.searchParams.set("x", document.querySelector("#x").value);
      url.searchParams.set("y", document.querySelector("#y").value);
      url.searchParams.set("z", document.querySelector("#z").value);

      window.location.href = url.toString();
    })
  })
  </script>
  <input id="x" />
  <input id="y" />
  <input id="z" />
  <button id="render">Render</button>
  <br />
  <img src="data:image/png;base64,${image}" />
  </body>
</html>`;

const server = http.createServer((req, res) => {
  const { pathname, searchParams } = new URL(req.url, `http://${req.headers.host}`);

  if (req.method !== "GET" || pathname !== "/") {
    res.writeHead(404, { "Content-Type": "text/plain" });
    res.end("Not Found");
    return;
  }

  const x = searchParams.get("x") || 3;
  const y = searchParams.get("y") || 3;
  const z = searchParams.get("z") || 3;

  execSync(`build/http-api-rendering ${x} ${y} ${z}`);
  const image = fs.readFileSync("build/api-out.png");
  const data = image.toString("base64");

  res.writeHead(200, { "Content-Type": "text/html" });
  res.end(html(x, y, z, data));
});

server.listen(3000, () => {
  console.log("Server listening on http://localhost:3000");
});
