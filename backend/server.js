require("dotenv").config();
const express = require("express");
const cors = require("cors");
const { Pool } = require("pg");

const app = express();
app.use(cors());
app.use(express.json());

const pool = new Pool({
  host: process.env.DB_HOST,
  port: process.env.DB_PORT,
  database: process.env.DB_NAME,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
});

// Auto-create table (mirrors the linked-list struct)
pool.query(`
  CREATE TABLE IF NOT EXISTS friends (
    id        SERIAL PRIMARY KEY,
    name      VARCHAR(50) NOT NULL UNIQUE,
    added_at  TIMESTAMP DEFAULT NOW()
  );
`).then(() => console.log("✅ Table ready"))
  .catch(err => console.error("❌ DB error:", err.message));

// GET /friends — display all (like displayFriends())
app.get("/friends", async (req, res) => {
  try {
    const result = await pool.query("SELECT * FROM friends ORDER BY id ASC");
    res.json(result.rows);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

// POST /friends — add friend (like addFriend())
app.post("/friends", async (req, res) => {
  const { name } = req.body;
  if (!name?.trim()) return res.status(400).json({ error: "Name is required." });
  try {
    const result = await pool.query(
      "INSERT INTO friends (name) VALUES ($1) RETURNING *",
      [name.trim()]
    );
    res.status(201).json(result.rows[0]);
  } catch (err) {
    if (err.code === "23505") return res.status(409).json({ error: "Friend already exists." });
    res.status(500).json({ error: err.message });
  }
});

// DELETE /friends/:name — remove friend (like removeFriend())
app.delete("/friends/:name", async (req, res) => {
  try {
    const result = await pool.query(
      "DELETE FROM friends WHERE name = $1 RETURNING *",
      [req.params.name]
    );
    if (result.rowCount === 0) return res.status(404).json({ error: "Friend not found." });
    res.json({ message: "Friend removed successfully." });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.listen(process.env.PORT, () =>
  console.log(`🚀 Server → http://localhost:${process.env.PORT}`)
);