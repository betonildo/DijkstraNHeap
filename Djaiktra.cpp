S = (V, A)
	if (dv pertence à Reais positivos e A pertence à arestas){
	
		ds = 0; dv = inf, para todo V pertencente aos vértices
    	visitado(v) = false
	    q = 0 (heap)
	    inserir(q, S /*vertice inicial*/)
	    while(!vazia(q)) {
            
            v = deletaOMenorDe(q)
            visitado(v) = true
            for (u que é vizinho(v) (N+)) {
            
                if (visitado(u) == false) {
                    if (du == inf) {
                        du = dv + dvu
                        inserir(q, (u, du))
                    }
                    else {
                        du = min(du, dv + dvu)
                        update(q, (u, du))
                    }
                }
            }
	    }
	}
	
