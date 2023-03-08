import express from 'express';
import cors from 'cors';
import movies from './api/movies.route.js';

const app = express();

app.use(cors());
app.use(express.json());

// all request with this url will be sentd to movies api
app.use("/api/v1/movies", movies);
// other should return a 404 error
app.use('*', (req, res) => {
	res.status(404).json({error: "not found"});
})

export default app;
