# nodejs1

A simple Express.js server for experimenting with Node.js concepts.

## Routes

| Route | Description |
|---|---|
| `GET /` | Returns a basic hello message |
| `GET /wacky` | Returns a random funny phrase (simulates a 500ms async response) |
| `GET /quote` | Fetches a random inspirational quote from [zenquotes.io](https://zenquotes.io) |
| `GET /quote-resolve` | Same as `/quote` but using `.then()` / `.catch()` promise chaining |

## Requirements

- [Node.js](https://nodejs.org) v18 or higher (for built-in `fetch` support)

## Install

```bash
npm install
```

## Run

**Production:**
```bash
npm start
```

**Development (auto-restarts on file changes):**
```bash
npm run start:dev
```

The server runs at `http://localhost:3000`.
