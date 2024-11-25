import { DataGrid, GridColDef } from '@mui/x-data-grid';
import { Box, Paper } from '@mui/material';
import CreateButton from './CreateButton';

const mockDataRows = [
    { id: 1, cardNumber: 'FJREIOFJ3' },
    { id: 2, cardNumber: 'ABCD1234' },
    { id: 3, cardNumber: 'XYZ7890' },
];

const columns: GridColDef[] = [
    { field: 'id', headerName: 'ID', width: 100, headerAlign: 'center', align: 'center' },
    { field: 'cardNumber', headerName: 'Card Number', width: 550, headerAlign: 'center', align: 'center' },
    {
        field: 'updateOption',
        headerName: '',
        width: 100,
        align: 'center',
        sortable: false,
        renderCell: (params) => (<a>Actualizar</a>)
    },
    {
        field: 'deleteOption',
        headerName: '',
        width: 100,
        align: 'center',
        sortable: false,
        renderCell: (params) => (<a>Eliminar</a>)
    }
];

export default function DataTable() {
    return (
        <Box
            sx={{
                display: 'flex',
                justifyContent: 'center',
                alignItems: 'center',
            }}
        >
            <Paper sx={{ height: 400, width: '60%' }}>
                <CreateButton/>
                <DataGrid
                    rows={mockDataRows}
                    columns={columns}
                    pageSizeOptions={[5, 10]}
                    paginationModel={{ page: 0, pageSize: 10 }}
                    disableRowSelectionOnClick={true}
                />
            </Paper>

        </Box>

    );
}
