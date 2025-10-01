<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8" />
<meta name="viewport" content="width=device-width,initial-scale=1" />
<title>FileConsole — Console File Manager (README)</title>
<style>
:root{
--bg:#0f1724; --card:#0b1220; --accent:#64d2ff; --muted:#94a3b8; --text:#e6eef8;
--success:#57d27a; --danger:#ff6b6b; --code-bg:#071023;
font-family: Inter, Roboto, "Segoe UI", system-ui, -apple-system, sans-serif;
}
html,body{height:100%;margin:0;background:linear-gradient(180deg,#071025 0%, #021026 100%);color:var(--text);}
.wrap{max-width:980px;margin:40px auto;padding:28px;background:linear-gradient(180deg, rgba(255,255,255,0.02), rgba(255,255,255,0.01));border-radius:12px;box-shadow:0 8px 30px rgba(2,6,23,0.6);}
header{display:flex;gap:16px;align-items:center}
h1{margin:0;font-size:28px}
p.lead{color:var(--muted);margin:6px 0 18px}


.badge{background:rgba(255,255,255,0.03);padding:6px 10px;border-radius:999px;color:var(--accent);font-weight:600;font-size:13px}


section{margin-top:20px}
h2{font-size:18px;margin:18px 0 8px}
.grid{display:grid;grid-template-columns:1fr 320px;gap:18px}


.card{background:var(--card);padding:14px;border-radius:10px;border:1px solid rgba(255,255,255,0.02)}
.muted{color:var(--muted);font-size:14px}


pre.code{background:var(--code-bg);padding:12px;border-radius:8px;overflow:auto;border:1px solid rgba(255,255,255,0.02);}
code{font-family:SFMono-Regular,Menlo,Monaco,Consolas,"Liberation Mono","Courier New",monospace;color:#cde7ff}


ul.commands{list-style:none;padding:0;margin:0}
ul.commands li{padding:8px 6px;border-radius:6px;margin-bottom:6px;background:linear-gradient(90deg, rgba(255,255,255,0.01), rgba(255,255,255,0.00));display:flex;justify-content:space-between;align-items:center}
.cmd{font-weight:700;color:var(--accent)}
.desc{color:var(--muted);font-size:13px}


.meta{display:flex;gap:12px;flex-wrap:wrap}
.meta div{background:rgba(255,255,255,0.02);padding:8px 10px;border-radius:8px;color:var(--muted);font-size:13px}


footer{margin-top:26px;color:var(--muted);font-size:13px;text-align:center}


@media(max-width:880px){.grid{grid-template-columns:1fr} .wrap{margin:18px;padding:16px}}
</style>
</head>
<body>
<div class="wrap">
<header>
<div>
<div class="badge">FileConsole</div>
<h1>FileConsole — Console File Manager</h1>
<p class="lead">Lightweight terminal file manager in C++ using the <code>&lt;filesystem&gt;</code> library.</p>
</div>
</header>


<section class="grid">
<div>
<div class="card">
<h2>Features</h2>
<ul class="muted">
<li>List directory contents with tags <code>[DIR]</code> / <code>[FILE]</code></li>
<li>Navigate folders with <code>cd</code> and go up with <code>..</code></li>
<li>Create folders and files (<code>mkdir</code>, <code>touch</code>)</li>
<li>Remove files/folders (<code>rm</code>, recursive for directories)</li>
<li>Rename (<code>rename</code>)</li>
<li>Copy inside the same folder (creates <code>copy_of_*</code>)</li>
<li>Move to another folder (<code>move</code>), supports <code>..</code> to move to parent</li>
<li>Search by mask in subfolders (supports <code>*</code> and <code>?</code> via regex)</li>
<li>Open files with the OS default application (<code>open</code>)</li>
<li>Compute size of files and folders (<code>size</code>)</li>
</ul>
</div>


<div class="card" style="margin-top:12px">
<h2>Requirements</h2>
<div class="muted">
<div>Compiler: <strong>g++ 8+</strong> / <strong>MSVC 2017+</strong> / <strong>clang 10+</strong></div>
<div>C++ standard: <strong>C++17</strong></div>
<div>Windows: run from PowerShell / cmd (uses <code>start</code> to open files)</div>
</div>
</div>


<div class="card" style="margin-top:12px">
<h2>Quick start (build example)</h2>
<pre class="code"><code>g++ main.cpp -o fileconsole -std=c++17


// if using older libstdc++ (GCC &lt; 8):
// g++ main.cpp -o fileconsole -std=c++17 -lstdc++fs


./fileconsole</code></pre>
</div>


<div class="card" style="margin-top:12px">
<h2>Safety notes</h2>
</html>
