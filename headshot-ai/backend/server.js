import express from 'express'
import cors from 'cors'
import multer from 'multer'

const app = express()
app.use(cors())
const upload = multer({ storage: multer.memoryStorage() })

app.post('/api/generate-headshot', upload.single('image'), async (req, res) => {
  if (!req.file) return res.status(400).json({ error: 'No file uploaded' })

  // Dummy implementation: echo back original image
  const originalImage = req.file.buffer.toString('base64')
  const generatedImage = originalImage // Replace with AI API call later

  res.json({ originalImage, generatedImage })
})

app.listen(5000, () => console.log('Backend running on http://localhost:5000'))
