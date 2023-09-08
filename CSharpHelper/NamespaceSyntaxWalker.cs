using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

/// <summary>A <see cref="CSharpSyntaxWalker"/> implementation for locating the namespace of a class.</summary>
public sealed class NamespaceSyntaxWalker : CSharpSyntaxWalker
{
    /// <summary>The name of the class to locate the namespace of.</summary>
    public string ClassName { get; }

    /// <summary>The namespace of the requested class.</summary>
    public string Namespace { get; private set; }

    /// <summary>Initializes a new <see cref="NamespaceSyntaxWalker"/> instance.</summary>
    /// <param name="className"></param>
    public NamespaceSyntaxWalker(string className)
    {
        Namespace = string.Empty;
        ClassName = className;
    }

    /// <inheritdoc/>
    public override void Visit(SyntaxNode? node)
    {
        if (node is TypeDeclarationSyntax type && type.Identifier.ValueText == ClassName)
        {
            for (var parent = node.Parent; parent != null; parent = parent.Parent)
            {
                // We don't want a nested type that happens to share its name
                // with the source file to result in a false-positive here.
                if (parent is TypeDeclarationSyntax)
                    break;

                if (parent is BaseNamespaceDeclarationSyntax ns)
                {
                    Namespace = ns.Name.ToString();
                    return;
                }
            }
        }

        base.Visit(node);
    }
}
