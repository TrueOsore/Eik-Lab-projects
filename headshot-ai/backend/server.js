import express from 'express'
import cors from 'cors'
import multer from 'multer'
import dotenv from 'dotenv'

dotenv.config()

const app = express()
const upload = multer({ storage: multer.memoryStorage() })

app.use(cors())

app.post('/api/generate-headshot', upload.single('image'), (req, res) => {
    const { style } = req.body

if (!req.file) {
    return res.status(400).json({ error: 'No image uploaded' })
}

// Mock generated image (reuse original)
const base64Image = req.file.buffer.toString('base64')

res.json({
    originalImage: base64Image,
    generatedImage: base64Image,
    style
    })
})

app.listen(5000, () => {
    console.log('Backend running on http://localhost:5000')
})