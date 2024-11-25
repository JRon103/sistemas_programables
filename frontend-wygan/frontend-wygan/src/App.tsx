// import { useState } from 'react'
// import reactLogo from './assets/react.svg'
// import viteLogo from '/vite.svg'
import './App.css'
import { Typography } from '@mui/material'
import DataTable from './components/DataTable'

function App() {

  return (
    <>
      <Typography align='center' variant='h3' sx={{ marginBottom: 2 }}>Control de Acceso</Typography>
      <DataTable/>
    </>
  )
}

export default App
