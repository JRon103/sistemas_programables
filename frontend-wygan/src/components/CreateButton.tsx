import { Button } from "@mui/material";
import { Box } from "@mui/system";

export default function CreateButton() {
    return (
        <Box
            sx={{
                display: 'flex',
                justifyContent: 'flex-start',
            }}
        >
            <Button variant="contained" sx={{ textTransform: 'none', marginBottom: 2 }}>
                Agregar
            </Button>
        </Box>
    )
}
